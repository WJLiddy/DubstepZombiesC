#include "mallparser.h"
#include <allegro5/allegro.h>
#include "../utils/common.h"
#include "malldraw.h"
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>

	MallParser::MallParser(ALLEGRO_BITMAP* base, ALLEGRO_BITMAP* always, std::set<Coord> collide, std::vector<MallObject> objects)
	{
		mallDraw = new MallDraw(base,always);
	}

	MallParser MallParser::parse(std::string pname)
	{
		ifstream in(pname+"mallscript.txt");
		// Load in the file at std string. throw exception if we could not.
		auto command_list = std::vector<std::vector<std::string>>(); 
		std::string str;
		while (std::getline(in, str)) 
		{
			//next if we read a newline or a space. 
			if(str.size() == 0 || str.at(0) == '#')
			{
				continue;
			}
			std::stringstream ss(str);
			std::istream_iterator<std::string> begin(ss);
			std::istream_iterator<std::string> end;
			command_list.push_back(std::vector<std::string> (begin, end));
		//std::copy(vstrings.begin(), vstrings.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
    	}
    	std::cout << "total mallscript command count: " << command_list.size() << "\n";

    	//Define some variables to collect command information.
    	ALLEGRO_BITMAP* always;
    	ALLEGRO_BITMAP* base;  
		
		//Ignore these guys for now.
		std::set<Coord> collide; 
		std::vector<MallObject> objects;

    	for(std::vector<std::vector<std::string>>::iterator it = command_list.begin(); it != command_list.end(); ++it) 
    	{
    		//turns out you can't use strings 
    		auto cmd = it[0].at(0);

    		if(cmd == "a")
    		{
    			std::string filename = (pname+it[0].at(1));
    			always = al_load_bitmap(filename.c_str());
    			if(!always)
    			{
    				std::cout << "MallScript error! No file named " << pname+it[0].at(1) << "\n";
    			}
   			}

    		if(cmd == "b")
    		{
    			std::string filename = pname+it[0].at(1);
    			base = al_load_bitmap(filename.c_str());
    			if(!base)
    			{
    				std::cout << "MallScript error! No file named " << pname+it[0].at(1) << "\n";
    			}
    		}
		}
		//Done, return a base and always with no objects or collide.
		return MallParser(base, always,collide, objects);
	}

