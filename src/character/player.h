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
	//move is discrete, so we can "charge" between frames.
	double delta_move_ = 0;

	const double SPEED_PER_FRAME = 0.7;
	const int draw_offset_x = -5;
	const int draw_offset_y = -10;

	const int spritesheet_size = 20;

	Coord validate_move(Coord delta, GameMap map);
public:
	//This'll be moved to a different class soon
	enum Direction {N = 0, NW = 1, W = 2, SW = 3, S = 4, SE = 5, E = 6, NE = 7};

	const int player_size = 10;

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
};
#endif 
