#include "mallparser.h"
#include <allegro5/allegro.h>
#include "../utils/common.h"
#include "malldraw.h"
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>

	std::unordered_set<Coord> MallParser::generateCollideMap(ALLEGRO_BITMAP* a)
	{
		std::unordered_set<Coord> collide;
		al_lock_bitmap(a, ALLEGRO_PIXEL_FORMAT_ANY_24_NO_ALPHA, ALLEGRO_LOCK_READONLY);
		for (int x = 0; x != al_get_bitmap_width(a); x++)
		{
			for (int y = 0; y != al_get_bitmap_height(a); y++)
			{
				ALLEGRO_COLOR c = al_get_pixel(a, x, y);
				if (c.r == 1.0f && c.g == 0.0f && c.b == 1.0f)
				{
					collide.emplace(x, y);
				}
			}
		}
		al_unlock_bitmap(a);
		return collide;
	}


	//TODO Raise exception on failure.
	std::vector<std::vector<std::string>> MallParser::tokenize(std::string pname)
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
		}
		return command_list;
	}

	MallParser::MallParser(ALLEGRO_BITMAP* base, ALLEGRO_BITMAP* always, std::unordered_set<Coord> ncollide, std::vector<MallObject> objects)
	{
		mallDraw = new MallDraw(base,always);
		collide = ncollide;
		mallObjects = objects;
	}

	MallParser MallParser::parse(std::string pname)
	{
		auto command_list = tokenize(pname);
		//[]() {};
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
			std::unordered_set<Coord> collide;
		};

		std::unordered_map<std::string, obj_info> object_template_list;

		std::vector<MallObject> mall_objects;

		for (std::vector<std::vector<std::string>>::iterator it = command_list.begin(); it != command_list.end(); ++it)
		{
			auto line = it[0];

			// a: always layer
			if (line.at(0) == "a")
			{
				std::string filename = (pname + line.at(1));
				always = al_load_bitmap(filename.c_str());
				if (!always)
				{
					throw "a (always) command: Error loading " + pname + line.at(1);
				}
			}

			// b: base layer
			if (line.at(0) == "b")
			{
				std::string filename = (pname + line.at(1));
				base = al_load_bitmap(filename.c_str());
				if (!base)
				{
					throw "b (base) command: Error loading " + pname + line.at(1);
				}
			}

			// c: collide layer
			if (line.at(0) == "c")
			{
				std::string filename = (pname + line.at(1));
				collide_bmp = al_load_bitmap(filename.c_str());
				if (!collide_bmp)
				{
					throw "c (collide) command: Error loading " + pname + line.at(1);
				}
				collide = generateCollideMap(collide_bmp);
			}

			// do: declare object non-animated
			// TODO this copies a lot of code from dao.
			if (line.at(0) == "do")
			{
				// Load in the bmp and collide. Also, make a struct that returns these two bitmaps.
				std::string objname = line.at(1);

				obj_info o;
				// push back the single animation
				o.draw.push_back(al_load_bitmap((pname + line.at(2)).c_str()));
				// push back the collide bitmap
				ALLEGRO_BITMAP* collide = al_load_bitmap((pname + line.at(3)).c_str());

				// If they could not be loaded, throw an error.
				if (!o.draw.at(0))
				{
					throw "do (declare-object) command: Error loading " + pname + line.at(2);
				}
				if (!collide)
				{
					throw "do (declare-object) command: Error loading " + pname + line.at(3);
				}

				//Good! now generate the collide map, and emplace a frametime of 1, and add the object name to the template list
				o.collide = generateCollideMap(collide);
				delete(collide);
				o.frametimes.push_back(1);
				object_template_list[objname]  =o;
			}

			// dao: declare object animated
			// example: dao fountain obj/fountain.bmp obj/f1.bmp 1 obj/f2.bmp 3
			if (line.at(0) == "dao")
			{
				//Load in the bmp and collide. Also, make a struct that returns these two bitmaps.
				std::string objname = line.at(1);
				obj_info o;
				ALLEGRO_BITMAP* collide = al_load_bitmap((pname + line.at(2)).c_str());

				if (!collide)
				{
					throw "dao (declare-animated-object) command: Error loading " + pname + line.at(3);
				}

				o.collide = generateCollideMap(collide);
				delete(collide);

				//iterate over last parts of vector. TODO: Check for proper arg count.
				for (int i = 3; i <  line.size(); i += 2)
				{
					ALLEGRO_BITMAP* a = al_load_bitmap((pname + line.at(i)).c_str());
					int ftime = std::stoi(line.at(i + 1));
					if (!a)
					{
						throw "dao (declare-animated-object) command: Error loading " + pname + line.at(i);
					}
					// Insert the frame and the time into the structures.
					o.draw.insert(o.draw.begin(),a);
					o.frametimes.insert(o.frametimes.begin(), ftime);
				}
				//done! add it to the list.
				object_template_list[objname] = o;
			}

			// p: place
			// example: fountain 233 2345
			if (line.at(0) == "p")
			{

				auto obj_temp_itr = object_template_list.find(it[0].at(1));
				if (obj_temp_itr == object_template_list.end())
				{
					throw "p (place) command: No object previously declared named " + line.at(1);
				}
				// Now we have the obj_info struct with the draw and body.
				auto obj = obj_temp_itr->second;

				Coord c = Coord(std::stoi(it[0].at(2)), std::stoi(it[0].at(3)));
				int h = al_get_bitmap_height(obj.draw.at(0));
				auto mall_object = MallObject(obj.draw, obj.frametimes, obj.collide, c, h);
				mall_objects.push_back(mall_object);
			}
		}


		//Done, return a base and always with no objects or collide.
		return MallParser(base, always, collide, mall_objects);

}
