#ifndef MALL_PARSER_H
#define MALL_PARSER_H

#include "../utils/common.h"
#include "malldraw.h"
#include "mallobject.h"
#include <allegro5/allegro.h>

class MallParser
{
private:
	//todo ??
	static std::unordered_set<Coord>  MallParser::generateCollideMap(ALLEGRO_BITMAP* a)
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
					collide.emplace(Coord(x, y));
				}
			}
		}
		al_unlock_bitmap(a);
		return collide;
	}
public:
	// TODO make private Base, Always, Map Object List, Collide layer, Map Object List
	MallParser(ALLEGRO_BITMAP*, ALLEGRO_BITMAP*, ALLEGRO_BITMAP*, std::unordered_set<Coord>, std::vector<MallObject>);
	static MallParser parse(std::string);
	MallDraw* mallDraw;
	std::vector<MallObject> mallObjects;
	std::unordered_set<Coord> collide;
};
#endif