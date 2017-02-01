#ifndef MALLDRAW_H
#define MALLDRAW_H
#include <allegro5/allegro.h>
#include "../utils/coord.h"
//Drawing information about the game map.
class MallDraw
{
private:
    ALLEGRO_BITMAP* base_;
    ALLEGRO_BITMAP* always_;
public:
	void draw_base(Coord);
	void draw_scan(Coord);
};
#endif 
