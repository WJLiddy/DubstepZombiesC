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
	ALLEGRO_BITMAP* debug_collide_;
public:
	MallDraw(ALLEGRO_BITMAP*,ALLEGRO_BITMAP*,ALLEGRO_BITMAP*);
	void draw_base(Coord);
	void draw_always(Coord);
	void draw_debug_collide(Coord);
};
#endif 
