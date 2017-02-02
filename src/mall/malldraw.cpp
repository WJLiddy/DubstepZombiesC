#include "malldraw.h"
#include "../utils/coord.h"
#include <allegro5/allegro.h>

	MallDraw::MallDraw(ALLEGRO_BITMAP* base,ALLEGRO_BITMAP* always,ALLEGRO_BITMAP* debug)
	{
		base_ = base;
		always_ = always;
		debug_collide_ = debug;
	}
	void MallDraw::draw_base(Coord camera)
	{
		al_draw_bitmap(base_,-camera.getX(),-camera.getY(),0);
	}
	void MallDraw::draw_always(Coord camera)
	{
		al_draw_bitmap(always_,-camera.getX(),-camera.getY(),0);
	}

	void MallDraw::draw_debug_collide(Coord camera)
	{
		al_draw_tinted_bitmap(debug_collide_, al_map_rgba_f(1, 1, 1, 0.2), -camera.getX(), -camera.getY(), 0);
	}

