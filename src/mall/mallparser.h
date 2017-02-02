#ifndef MALL_PARSER_H
#define MALL_PARSER_H

#include "../utils/common.h"
#include "malldraw.h"
#include "mallobject.h"
#include <allegro5/allegro.h>

class MallParser
{
public:
	// TODO make private Base, Always, Map Object List, Collide layer, Map Object List
	MallParser(ALLEGRO_BITMAP*, ALLEGRO_BITMAP*, ALLEGRO_BITMAP*, std::unordered_set<Coord>, std::vector<MallObject>);
	static MallParser parse(std::string);
	MallDraw* mallDraw;
	//std::vector<MallObject> mallObjects;
	std::unordered_set<Coord> collide;
};
#endif