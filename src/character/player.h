#ifndef PLAYER_H
#define PLAYER_H
#include <allegro5/allegro.h>
#include "../utils/gameobject.h"
#include "../input/controller.h"

//Drawing information about the game map.
class Player : public GameObject
{
private:
    ALLEGRO_BITMAP* walk_;
	//TODO: AnimationSet class, like in Ad2.
	int frame = 0;
	int frame_time_left_ = 0;
	void setDirection(int, int);
	double potential_ = 0;
public:
	//This'll be moved to a different class in the real version
	enum Direction { N = 0, NW = 1, W = 2, SW = 3, S = 4, SE = 5, E = 6, NE = 7};
	Direction dir = N;
    Player();

	void update(Controller&,unordered_set<Coord>& collide); //Here is where I'd implement ted's game map
	void draw(Coord&);
};
#endif 
