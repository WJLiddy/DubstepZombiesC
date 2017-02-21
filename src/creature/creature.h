#ifndef CREATURE_H
#define CREATURE_H
#include <allegro5/allegro.h>
#include "../utils/gameobject.h"
#include "../input/controller.h"
#include "../utils/renderobject.h"
#include "../utils/gamemap.h"

class Creature : public RenderObject
{
public:
	//Firstly, declare the direction enum.

	//Directional utils
	enum Direction { N = 0, NW = 1, W = 2, SW = 3, S = 4, SE = 5, E = 6, NE = 7 };

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

	// We also have this, which is an important part of this class.
	struct Anim_set {
		int frame_size;
		int frame_count;
		int frame_speed;
		int draw_offset_x;
		int draw_offset_y;
		ALLEGRO_BITMAP* anim;
	};


protected:

	// current frame of walk animation we are on,
	int frame = 0;

	// Time left in the frame.
	int frame_time_left_ = 0;

	// Move is discrete, so we can "charge" between frames.
	double delta_move_ = 0;

	//Helper method: Checks if move is legal. Only works for deltas of +/- 1 !
	Coord validate_move(Coord delta, GameMap& map)
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

	// reset the frames if we are not moving.
	void idle()
	{			//Set player frame to 0, cancel any move delta, do not move animation
				//This behavior may be overridden
		frame = 0;
		frame_time_left_ = 1;
		delta_move_ = 0;
	}

	void attempt_move(Direction moveDir, GameMap& map)
	{
		//See if player can even move. If they can't, return.
		Coord delta = toDeltaCoord(moveDir);
		auto valid_delta = validate_move(delta, map);
		dir = moveDir;
		if (valid_delta == Coord(0, 0))
		{
			//you can't move here!
			//Set player frame to 0, idle
			idle();
			return;
		}

		// Otherwise, we can move here, at least in one of the directions.
		// let animation run.
		frame_time_left_--;
		if (frame_time_left_ <= 0)
		{
			// h a r d c o d e d
			frame_time_left_ = walk.frame_speed;
			frame = ((frame + 1) % walk.frame_count);
		}
		// Add move to our delta timer.
		delta_move_ += move_speed();

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


public:

	const int player_size = 10;

	Direction dir = N;

	int getBottom()
	{
		return getCoord().getY() + player_size;
	}

	void draw(Coord& camera)
	{

		int dir_offset = static_cast<int>(dir);
		al_draw_bitmap_region(walk.anim, frame*walk.frame_size, dir_offset*walk.frame_size, walk.frame_size, walk.frame_size, (getCoord().getX() + walk.draw_offset_x) - camera.getX(), (getCoord().getY() + walk.draw_offset_y) - camera.getY(), 0);
		//al_draw_bitmap_region(walk_,w*frame, h*dir_offset, w, h, coord.getX() - camera.getX(), coord.getY() - camera.getY(), 0);
	}
	
	virtual double move_speed() = 0;
	Anim_set walk;

	Creature(Coord c, std::string id, Anim_set walk_anim) : RenderObject(c, id, Coord::generateRect(player_size, player_size))
	{
		walk = walk_anim;
	};
};
#endif 
