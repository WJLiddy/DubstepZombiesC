#ifndef MALL_PARSER_H
#define MALL_PARSER_H

#include "../utils/common.h"
#include "malldraw.h"
#include "mallobject.h"
#include <allegro5/allegro.h>

class MallParser
{
private:

	// Generate body from pink pixels of bitmap
	static std::unordered_set<Coord>  generateCollideMap(ALLEGRO_BITMAP* a);
	static std::vector<std::vector<std::string>> tokenize(std::string pname);

public:
	// Base, always, collide base, objects.
	MallParser(ALLEGRO_BITMAP*, ALLEGRO_BITMAP*, std::unordered_set<Coord>, std::vector<MallObject>);

	// Returns a MallParser object if MallScript could be parsed. Otherwise throw an exeception
	static MallParser parse(std::string);

	// Returns the objects parsed from MallScript.
	MallDraw* mallDraw;
	std::vector<MallObject> mallObjects;
	std::unordered_set<Coord> collide;
};
#endif