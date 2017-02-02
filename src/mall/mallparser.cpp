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

		//Ignore these guys for now.
		std::unordered_set<Coord> collide;
		std::vector<MallObject> objects;

		for (std::vector<std::vector<std::string>>::iterator it = command_list.begin(); it != command_list.end(); ++it)
		{
			//turns out you can't use strings 
			auto cmd = it[0].at(0);

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
				al_lock_bitmap(collide_bmp, ALLEGRO_PIXEL_FORMAT_ANY_24_NO_ALPHA, ALLEGRO_LOCK_READONLY);
				for (int x = 0; x != al_get_bitmap_width(collide_bmp); x++)
				{
					for (int y = 0; y != al_get_bitmap_height(collide_bmp); y++)
					{
						ALLEGRO_COLOR c = al_get_pixel(collide_bmp, x, y);
						if (c.r == 1.0f && c.g == 0.0f && c.b == 1.0f)
						{
							collide.emplace(Coord(x, y));
						}

					}
				}
				al_unlock_bitmap(collide_bmp);
				std::cout << "  found " << collide.size() << "\n";
			}

			//do vending_west obj/vending_west.bmp obj/vending_west_c.bmp
			//dao fountain obj/fountain.bmp obj/f1.bmp 1 obj/f2.bmp 3
			if (cmd == "do")
			{
				/**
				//Load in the bmp and collide. Also, make a struct that returns these two bitmaps.
				std::string filename = pname + it[0].at(1);
				base = al_load_bitmap(filename.c_str());
				if (!base)
				{
					std::cout << "MallScript error! No file named " << pname + it[0].at(1) << "\n";
				}
				*/
			}

			}
			//Done, return a base and always with no objects or collide.
			return MallParser(base, always, collide_bmp, collide, objects);

}

