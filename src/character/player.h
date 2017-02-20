#ifndef PLAYER_H
#define PLAYER_H
#include <allegro5/allegro.h>
#include "../utils/gameobject.h"
#include "../input/controller.h"
#include "../utils/renderobject.h"
#include "../utils/gamemap.h"


//Drawing information about the game map.
class Player : public RenderObject
{

private:
    ALLEGRO_BITMAP* walk_;

	//TODO: AnimationSet class, like in Ad2.
	int frame = 0;
	int frame_time_left_ = 0;
	static const int spritesheet_size_ = 24;
	static const int frame_count_ = 8;
	static const int frame_speed_ = 5;

	//move is discrete, so we can "charge" between frames.
	double delta_move_ = 0;



	// DO NOT SET ABOVE 1.0. The algorithm used is not designed to go faster than 1.0.
	const double BASE_SPEED = 0.9;

	int stamina_ = 0;
	int thirst_ = 0;
	int hunger_ = 0;
	int infection_ = 0;
	bool infected_ = false;

	// Total amount of stamina that can be carried per energy unit.
	static const int STAMINA_REGEN_PER_ENERGY = 1;
	
	static const int THIRST_RATE = 1;
	static const int HUNGER_RATE = 1;

	static const int BASE_ENERGY = 5;

	// one minute each, for testing. 
	//At thirst mach 1, you complain. At thrist mach 2, you get a -1 stamina debuff, so on, until your stamina level reaches 0. Then you die
	static const int THIRST_MACH = (7 * 60);
	static const int HUNGER_MACH = (11 * 60);

	Coord validate_move(Coord delta, GameMap& map);
public:
	//This'll be moved to a different class soon
	enum Direction {N = 0, NW = 1, W = 2, SW = 3, S = 4, SE = 5, E = 6, NE = 7};

	static int player_size;
	static int draw_offset_x;
	static int draw_offset_y;

	Coord toDeltaCoord(Direction d)
	{
		switch (d)
		{
		case N: return Coord(0, -1);
		case NE: return Coord(1, -1);
		case E: return Coord(1, 0);
		case SE: return Coord(1, 1);
		case S: return Coord(0, 1);
		case SW: return Coord(-1, 1);
		case W: return Coord(-1, 0);
		case NW: return Coord(-1, -1);
		}

	}

	bool cardinal(Direction d)
	{
		return (d == N || d == W || d == S || d == E);
	}

	Direction dir = N;
    Player();

	void update(Controller& ,GameMap& gm); 
	void draw(Coord&);
	int getBottom();

	//BASE_ENERGY(), being totally healthy. 0, being dead.
	int getEnergyCount();
	
	//some constant times energy level
	int getMaxStamina();

	int getStaminaLevel();

	// I love Java!
	int getEnergyMissingDueToInfection();
	int getEnergyMissingDueToThirst();
	int getEnergyMissingDueToHunger();

	int getBaseEnergy();

	static const int STAMINA_PER_ENERGY = 500;

};
#endif 
