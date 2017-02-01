#include "mallparser.h"
#include "../utils/common.h"
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>

	MallParser::MallParser(ALLEGRO_BITMAP* base, ALLEGRO_BITMAP* always, std::set<Coord> collide, std::vector<MallObject> objects)
	{

	}

	MallParser MallParser::parse(std::string fname)
	{
		ifstream in(fname);
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
    	for(std::vector<std::vector<std::string>>::iterator it = command_list.begin(); it != command_list.end(); ++it) 
    	{
    		//turns out you can't use strings 
    		auto cmd =  it[0].at(0);
    		if(cmd == "a")
    		{

    		}
    		if(cmd == "b")
    		{

    		}
		}

    // now we loop back and get the next line in 'str'

	}
	
	MallDraw MallParser::mallDraw()
	{

	}

	std::vector<MallObject> MallParser::mallObjects()
	{

	}
	std::set<Coord> MallParser::collide()
	{

	}

