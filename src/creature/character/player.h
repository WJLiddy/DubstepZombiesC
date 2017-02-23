#ifndef PLAYER_H
#define PLAYER_H
#include <allegro5/allegro.h>
#include "../../utils/gameobject.h"
#include "../../input/controller.h"
#include "../../utils/renderobject.h"
#include "../../utils/gamemap.h"
#include "../creature.h"


//Drawing information about the game map.
class Player : public Creature
{

private:

	int stamina_ = 0;
	int thirst_ = 0;
	int hunger_ = 0;
	int infection_ = 0;
	bool infected_ = false;



public:

	static Anim_set generate_anim_set()
	{
		Creature::Anim_set a;
		a.frame_count = 8;
		a.frame_speed = 5;
		a.frame_size = 24;
		a.draw_offset_x = -7;
		a.draw_offset_y = -13;
		a.anim = al_load_bitmap("res/sprites/jacket/walk.png");
		return a;
	}

	// Total amount of stamina that can be carried per energy unit.
	static const int STAMINA_REGEN_PER_ENERGY = 1;

	static const int THIRST_RATE = 1;
	static const int HUNGER_RATE = 1;

	static const int BASE_ENERGY = 5;

	static const int STAMINA_PER_ENERGY = 500;

	const double MOVE_SPEED = 0.9;


	// one minute each, for testing. 
	//At thirst mach 1, you complain. At thrist mach 2, you get a -1 stamina debuff, so on, until your stamina level reaches 0. Then you die
	static const int THIRST_MACH = (7 * 60);
	static const int HUNGER_MACH = (11 * 60);

    Player();

	void update(Controller& ,GameMap& gm); 

	//BASE_ENERGY(), being totally healthy. 0, being dead.
	int getEnergyCount();
	
	//some constant times energy level
	int getMaxStamina();

	int getStaminaLevel();

	// I love Java!
	int getEnergyMissingDueToInfection();
	int getEnergyMissingDueToThirst();
	int getEnergyMissingDueToHunger();

	double move_speed();



};
#endif 
