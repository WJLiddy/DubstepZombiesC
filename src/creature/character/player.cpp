#define NOMINMAX


#include "player.h"
#include "../../utils/coord.h"
#include "../../utils/gameobject.h"
#include <allegro5/allegro.h>
#include "../../input/controller.h"
#include "../../utils/common.h"


	//Player hardcoded to be 10 by 10 for now.
	Player::Player() : Creature(Coord(50,50),"PLAYER", Player::generate_anim_set())
	{
		
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



	Creature::Direction getInputtedDirection(Controller& c)
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
		auto p = map.collect("PLAYER")[0];
		printf("x: %d y: %d \n", p->getCoord().getX(), p->getCoord().getY());
		thirst_ += THIRST_RATE;
		hunger_ += HUNGER_RATE;
        stamina_ = std::min(getMaxStamina(), stamina_ + getEnergyCount() * STAMINA_REGEN_PER_ENERGY);
		

		if(!move_intended(i))
		{ 
			idle();
		}
		else
		{	
			attempt_move(getInputtedDirection(i), map);
		}
		return;
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

	int Player::getStaminaLevel()
	{
		return stamina_;
	}

	double Player::move_speed()
	{
		return MOVE_SPEED;
	}