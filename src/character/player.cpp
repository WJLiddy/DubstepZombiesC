#include "player.h"
#include "../utils/coord.h"
#include "../utils/gameobject.h"
#include <allegro5/allegro.h>
#include "../input/controller.h"

	Player::Player() : GameObject(Coord(50,50),20,20)
	{
		walk_ = al_load_bitmap("res/sprites/jacket/walk.png");
	}
	void Player::update(Controller& i)
	{
        return;
	}
	void Player::draw(Coord& camera)
	{
		al_draw_bitmap(walk_,0,0,0);
	}

