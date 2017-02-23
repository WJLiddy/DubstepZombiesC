#ifndef ZOMBIE_H
#define ZOMBIE_H
#include <allegro5/allegro.h>
#include "../../utils/gameobject.h"
#include "../../input/controller.h"
#include "../../utils/renderobject.h"
#include "../../utils/gamemap.h"
#include "../creature.h"


//Drawing information about the game map.
class Zombie : public Creature
{

private:


	// DO NOT SET ABOVE 1.0. The algorithm used is not designed to go faster than 1.0.
	const double BASE_SPEED = 0.4;


public:
	static Anim_set generate_anim_set()
	{

			Creature::Anim_set a;
			a.frame_count = 4;
			a.frame_speed = 15;
			a.frame_size = 20;
			a.draw_offset_x = -5;
			a.draw_offset_y = -10;
			a.anim = al_load_bitmap("res/sprites/zombie/walk.png");
			return a;
	}
	 
	Zombie(Coord c);
	void update(GameMap& gm); 
	double move_speed()
	{
		return 0.4;
	}
};
#endif 
