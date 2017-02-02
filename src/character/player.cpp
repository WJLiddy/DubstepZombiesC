#include "malldraw.h"
#include "../utils/coord.h"
#include <allegro5/allegro.h>

	MallDraw::MallDraw(ALLEGRO_BITMAP* base,ALLEGRO_BITMAP* always)
	{
		base_ = base;
		always_ = always;
	}
	void MallDraw::draw_base(Coord camera)
	{
		al_draw_bitmap(base_,-camera.getX(),-camera.getY(),0);
	}
	void MallDraw::draw_always(Coord camera)
	{
		al_draw_bitmap(always_,-camera.getX(),-camera.getY(),0);
	}

