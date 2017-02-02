#include "mallparser.h"
#include <allegro5/allegro.h>
#include "../utils/common.h"
#include "malldraw.h"
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>

	MallParser::MallParser(ALLEGRO_BITMAP* base, ALLEGRO_BITMAP* always, ALLEGRO_BITMAP* debug_collide, std::unordered_set<Coord> ncollide, std::vector<MallObject> objects)
	{
		mallDraw = new MallDraw(base,always,debug_collide);
		collide = ncollide;
	}

	// this will need refactoring.
	MallParser MallParser::parse(std::string pname)
	{
		ifstream in(pname + "mallscript.txt");
		// Load in the file at std string. throw exception if we could not.
		auto command_list = std::vector<std::vector<std::string>>();
		std::string str;
		while (std::getline(in, str))
		{
			//next if we read a newline or a space. 
			if (str.size() == 0 || str.at(0) == '#')
			{
				continue;
			}
			std::stringstream ss(str);
			std::istream_iterator<std::string> begin(ss);
			std::istream_iterator<std::string> end;
			command_list.push_back(std::vector<std::string>(begin, end));
			//std::copy(vstrings.begin(), vstrings.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
		}
		std::cout << "total mallscript command count: " << command_list.size() << "\n";

		//Define some variables to collect command information.
		ALLEGRO_BITMAP* always;
		ALLEGRO_BITMAP* base;
		ALLEGRO_BITMAP* collide_bmp;

		//Collide coord points for the mall base layer.
		std::unordered_set<Coord> collide;

		//Struct to temporarily store object information until it is placed.
		struct obj_info
		{
			std::vector<ALLEGRO_BITMAP*> draw;
			std::vector<int> frametimes;
			ALLEGRO_BITMAP* debug_collide;
			std::unordered_set<Coord> collide;
		};

		std::unordered_map<std::string, obj_info> object_template;

		std::vector<MallObject> mall_objects;

		for (std::vector<std::vector<std::string>>::iterator it = command_list.begin(); it != command_list.end(); ++it)
		{
			//turns out you can't use strings 
			auto cmd = it[0].at(0);
			std::cout << "EXECUTING: " << it[0].at(0) << " " << it[0].at(1) << "\n";
			if (cmd == "a")
			{
				std::string filename = (pname + it[0].at(1));
				always = al_load_bitmap(filename.c_str());
				if (!always)
				{
					std::cout << "MallScript error! No file named " << pname + it[0].at(1) << "\n";
				}
			}

			if (cmd == "b")
			{
				std::string filename = pname + it[0].at(1);
				base = al_load_bitmap(filename.c_str());
				if (!base)
				{
					std::cout << "MallScript error! No file named " << pname + it[0].at(1) << "\n";
				}
			}

			//collide apporach is kinda naive, but that's ok for now
			if (cmd == "c")
			{
				std::string filename = pname + it[0].at(1);
				collide_bmp = al_load_bitmap(filename.c_str());
				if (!collide_bmp)
				{
					std::cout << "MallScript error! No file named " << pname + it[0].at(1) << "\n"; \
						continue;
				}

				//ok. Iterate through the map, and find the collission. This is gonna be slow, for now.
				std::cout << "Finding colissions...";
				collide = generateCollideMap(collide_bmp);
				std::cout << "  found " << collide.size() << "\n";
			}

			//do vending_west obj/vending_west.bmp obj/vending_west_c.bmp
			if (cmd == "do")
			{
				//Load in the bmp and collide. Also, make a struct that returns these two bitmaps.
				std::string objname = it[0].at(1);
				obj_info o;
				o.draw.push_back(al_load_bitmap((pname + it[0].at(2)).c_str()));
				o.debug_collide = al_load_bitmap((pname + it[0].at(3)).c_str());
				if (!o.draw.at(0))
				{
					std::cout << "MallScript error! Can't find " << pname + it[0].at(2) << "\n";
				}
				if ( !o.debug_collide)
				{
					std::cout << "MallScript error! Can't find " << pname + it[0].at(3) << "\n";
				}

				o.collide = generateCollideMap(o.debug_collide);
				o.frametimes.emplace_back(0);
				object_template.emplace(objname, o);
			}

			//dao fountain obj/fountain.bmp obj/f1.bmp 1 obj/f2.bmp 3
			if (cmd == "dao")
			{
				//Load in the bmp and collide. Also, make a struct that returns these two bitmaps.
				std::string objname = it[0].at(1);
				obj_info o;
				o.debug_collide = al_load_bitmap((pname + it[0].at(2)).c_str());
				o.collide = generateCollideMap(o.debug_collide);
				//iterate over last parts of vector. TODO: Check for proper arg count.
				for (int i = 3; i < it[0].size(); i += 2)
				{
					ALLEGRO_BITMAP* a = al_load_bitmap((pname + it[0].at(i)).c_str());
					int ftime = std::stoi(it[0].at(i + 1));
					if (!a || !o.debug_collide)
					{
						std::cout << "MallScript error! No file named " << pname + it[0].at(1) << "\n";
					}
					o.draw.insert(o.draw.begin(),a);
					o.frametimes.insert(o.frametimes.begin(), ftime);
				}
				object_template.emplace(objname, o);
			}

			if (cmd == "p")
			{
				
				//Finally, you place objects like this, using p (put)
				//For now, objects are static, so we just place the coords on the mall base layer.
				//Throw error if obj cannot be found!
				auto obj_temp_itr = object_template.find(it[0].at(1));
				if (obj_temp_itr == object_template.end())
				{
					std::cout << "MallScript error! No object declared named " << it[0].at(1) << "\n";
				}
				auto obj = obj_temp_itr->second;
				Coord c = Coord(std::stoi(it[0].at(2)), std::stoi(it[0].at(3)));
				int w = al_get_bitmap_width(obj.draw.at(0));
				int h = al_get_bitmap_height(obj.draw.at(0));
				std::cout << "finishing\n";
				auto mall_object = MallObject(obj.draw, obj.frametimes, c, w, h);
				//add mall object to list, add coords into the collide set (FOR NOW).
				std::cout << "Placing! \n";
				for (const auto& elem : obj.collide) 
				{
					auto collide_coord = Coord(elem.getX() + mall_object.coord.getX(), elem.getY() + mall_object.coord.getY());
					collide.emplace(collide_coord);
				}
				mall_objects.emplace_back(mall_object);
			}
		}
		std::cout << "Script Run! \n";


			//Done, return a base and always with no objects or collide.
			return MallParser(base, always, collide_bmp, collide, mall_objects);

}
