#ifndef PLAYER_H
#define PLAYER_H
#include <allegro5/allegro.h>
#include "../utils/gameobject.h"
#include "../input/controller.h"

//Drawing information about the game map.
class Player : GameObject
{
private:
    ALLEGRO_BITMAP* walk_;
public:
    Player();
    void update(Controller&); //Here is where I'd implement ted's game map
	void draw(Coord&);
};
#endif 
