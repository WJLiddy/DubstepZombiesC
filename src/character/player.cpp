#include "player.h"
#include "../utils/coord.h"
#include "../utils/gameobject.h"
#include <allegro5/allegro.h>
#include "../input/controller.h"

	Player::Player() : GameObject(Coord(50,50),20,20)
	{
		walk_ = al_load_bitmap("res/sprites/jacket/walk.png");
	}

	void Player::setDirection(int dx, int dy)
	{
		switch (dx)
		{
		case -1:
			switch (dy)
			{
			case -1:dir = NW; break;
			case 0:dir = W; break;
			case 1:dir = SW; break;
			}
			break;
		case 0:
			switch (dy)
			{
			case -1:dir = N; break;
			//This is an ungly shotcut, but, it will work for now.
			case 0:frame = 0; frame_time_left_ = 1; potential_ = 0; break;
			case 1:dir = S; break;
			}
			break;
		case 1:
			switch (dy)
			{
			case -1:dir = NE;break;
			case 0:dir = E; break;
			case 1:dir = SE; break;
			}
		}
	}
	//temp temp temp
	void Player::update(Controller& i, unordered_set<Coord>& collide)
	{

		int dx = 0;
		int dy = 0;
		//Do you like hardcoding?
		if (i.pressed(Controller::UP))
			dy = -1;
		else if (i.pressed(Controller::DOWN))
			dy = 1;
		if (i.pressed(Controller::LEFT))
			dx = -1;
		else if (i.pressed(Controller::RIGHT))
			dx = 1;
		
		//dirty hardcoding
		potential_ += 0.7;
		if (potential_ >= 1)
		{
			potential_ -= 1;
			//Crappy naieve approach, deal for now until ted makes map class
			coord = Coord(coord.getX() + dx, coord.getY() + dy);

			bool breakflag = false;
			//10 by 10 at 5 10
			for (int x = coord.getX() + 5; !breakflag && x != coord.getX() + 15 ; x++)
			{
				for (int y = coord.getY() + 10; !breakflag && y != coord.getY() + 20; y++)
				{
					//if collide, undo move, and 
					if (collide.find(Coord(x,y)) != collide.end())
					{
						breakflag = true;
						//unmove
						coord = Coord(coord.getX() - dx, coord.getY() - dy);
					}
				}
			}

			
		}

		frame_time_left_--;
		if (frame_time_left_ <= 0)
		{
			frame_time_left_ = 15;
			frame = ((frame + 1) % 4);
		}

		setDirection(dx, dy);

		return;
	}
	void Player::draw(Coord& camera)
	{
		
		int dir_offset = static_cast<int>(dir);
		al_draw_bitmap_region(walk_, frame*w, dir_offset*h, w, h, coord.getX() - camera.getX(), coord.getY() - camera.getY(), 0);

		//al_draw_bitmap_region(walk_,w*frame, h*dir_offset, w, h, coord.getX() - camera.getX(), coord.getY() - camera.getY(), 0);
	}

