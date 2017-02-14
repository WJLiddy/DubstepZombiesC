#define NOMINMAX


#include "player.h"
#include "../utils/coord.h"
#include "../utils/gameobject.h"
#include <allegro5/allegro.h>
#include "../input/controller.h"
#include "../utils/common.h"

int Player::player_size = 10;
int  Player::draw_offset_x = -5;
int  Player::draw_offset_y = -10;

	//Player hardcoded to be 10 by 10 for now.
	Player::Player() : RenderObject(Coord(50,50),"PLAYER",Coord::generateRect(player_size, player_size))
	{
		walk_ = al_load_bitmap("res/sprites/jacket/walk.png");
	}

	bool move_intended(Controller& c)
	{
		auto move_btns = { Controller::UP, Controller::DOWN, Controller::LEFT, Controller::RIGHT };
		for (auto control : move_btns)
		{
			if (c.pressed(control))
				return true;
		}
		return false;
	}

	Coord Player::validate_move(Coord delta, GameMap& map)
	{
		//Iterate along left side and look for collision. Will not work if player move speed is greater than 1. 
		if (delta.getX() == 1)
		{
			for (int dy = 0; dy != player_size; dy++)
			{
				if (map.get(getCoord() + Coord(player_size, dy)).size() > 0)
				{
					//cancel move and break
					delta.setX(0);
					break;
				}
			}
		}

		//Iterate along right side and look
		if (delta.getX() == -1)
		{
			for (int dy = 0; dy != player_size; dy++)
			{
				if (map.get(getCoord() + Coord(-1, dy)).size() > 0)
				{
					//cancel move and break
					delta.setX(0);
					break;
				}
			}
		}

		//Iterate along top side and look for collision. Will not work if player move speed is greater than 1. 
		if (delta.getY() == -1)
		{
			for (int dx = 0; dx != player_size; dx++)
			{
				if (map.get(getCoord() + Coord(dx, -1)).size() > 0)
				{
					//cancel move and break
					delta.setY(0);
					break;
				}
			}
		}

		//Iterate along bottom and look
		if (delta.getY() == 1)
		{
			for (int dx = 0; dx != player_size; dx++)
			{
				if (map.get(getCoord() + Coord(dx, player_size)).size() > 0)
				{
					//cancel move and break
					delta.setY(0);
					break;
				}
			}
		}

		return delta;
	}

	Player::Direction getInputtedDirection(Controller& c)
	{

		if (c.pressed(Controller::UP) && c.pressed(Controller::RIGHT))
			return Player::NE;
		if (c.pressed(Controller::UP) && c.pressed(Controller::LEFT))
			return Player::NW;
		if (c.pressed(Controller::DOWN) && c.pressed(Controller::RIGHT))
			return Player::SE;
		if (c.pressed(Controller::DOWN) && c.pressed(Controller::LEFT))
			return Player::SW;

		if (c.pressed(Controller::UP))
			return Player::N;
		if (c.pressed(Controller::LEFT))
			return Player::W;
		if (c.pressed(Controller::RIGHT))
			return Player::E;
		if (c.pressed(Controller::DOWN))
			return Player::S;
	}

	void Player::update(Controller& i, GameMap& map)
	{
		thirst_ += THIRST_RATE;
		hunger_ += HUNGER_RATE;
        stamina_ = std::min(getMaxStamina(), stamina_ + getEnergyCount() * STAMINA_REGEN_PER_ENERGY);
		

		if(!move_intended(i))
		{ 
			//Set player frame to 0, cancel any move delta, do not move animation
			frame = 0;
			frame_time_left_ = 1;
			delta_move_ = 0;
		}
		else
		{
			//See if player can even move. If they can't, return.
			auto moveDir = getInputtedDirection(i);
			Coord delta = toDeltaCoord(moveDir);
			auto valid_delta = validate_move(delta, map);
			dir = moveDir;
			if (valid_delta == Coord(0, 0))
			{
				//you can't move here!
				//Set player frame to 0, cancel any move delta, do not move animation
				frame = 0;
				frame_time_left_ = 1;
				delta_move_ = 0;
				return;
			}
			
			// Otherwise, we can move here, at least in one of the directions.
			// let animation run.

			frame_time_left_--;
			if (frame_time_left_ <= 0)
			{
				// h a r d c o d e d
				frame_time_left_ = 15;
				frame = ((frame + 1) % 4);
			}
			




			//Speed calc
			double speed = BASE_SPEED;

			// Add move to our delta timer.
			delta_move_ += speed;

			// See if our delta timer triggers an update.
			bool move_flag = false;
			if (delta_move_ >= 1 && cardinal(moveDir))
			{
				move_flag = true;
				delta_move_ -= 1;
			}

			//radical 2
			if (delta_move_ >= 1.4 && !cardinal(moveDir))
			{
				move_flag = true;
				delta_move_ -= 1.4;
			}

			if (move_flag)
			{
				map.move(*this, getCoord() + valid_delta);				
			}
		}
		return;
	}
	void Player::draw(Coord& camera)
	{
		
		int dir_offset = static_cast<int>(dir);
		al_draw_bitmap_region(walk_, frame*spritesheet_size, dir_offset*spritesheet_size, spritesheet_size, spritesheet_size, (getCoord().getX() + draw_offset_x) - camera.getX(), (getCoord().getY() + draw_offset_y) - camera.getY(), 0);

		//al_draw_bitmap_region(walk_,w*frame, h*dir_offset, w, h, coord.getX() - camera.getX(), coord.getY() - camera.getY(), 0);
	}

	int Player::getBottom()
	{
		return getCoord().getY() + player_size;
	}

	// I love Java!
	int Player::getEnergyMissingDueToInfection()
	{
		return infection_;
	}

	int Player::getEnergyMissingDueToThirst()
	{
		return std::max(0, (thirst_ / THIRST_MACH) - 1);
	}

	int Player::getEnergyMissingDueToHunger()
	{
		return std::max(0, (hunger_ / HUNGER_MACH) - 1);
	}
	int Player::getEnergyCount()
	{
		return std::max(0,BASE_ENERGY + -(getEnergyMissingDueToHunger() + getEnergyMissingDueToInfection() + getEnergyMissingDueToThirst()));
	}

	//some constant times energy level
	int Player::getMaxStamina()
	{
		return getEnergyCount() * STAMINA_PER_ENERGY;
	}

	int Player::getBaseEnergy()
	{
		return BASE_ENERGY;
	}


	int Player::getStaminaLevel()
	{
		return stamina_;
	}
