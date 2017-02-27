
#include "zombie.h"
#include "../../utils/coord.h"
#include "../../utils/gameobject.h"
#include <allegro5/allegro.h>
#include "../../input/controller.h"
#include "../../utils/common.h"

//Player hardcoded to be 10 by 10 for now.
Zombie::Zombie(Coord c) : Creature(c, "ZOMBIE", generate_anim_set())
{

}
void Zombie::update(GameMap& gm)
{
	//get player location(s)
	auto players = gm.collect("PLAYER");
	// calc some dxs and dys
	
	auto delt = players[0]->getCoord() - getCoord();
	//printf("x: %d y: %d \n", getCoord().getX(), getCoord().getY());
	//printf("x: %d y: %d \n", delt.getX(), delt.getY());
	/**
	if(delt.getX() > 0 && delt.getY() > 0)
		attempt_move(NW, gm);
	if (delt.getX() > 0 && delt.getY() < 0)
		attempt_move(SW, gm);
	if (delt.getX() < 0 && delt.getY() > 0)
		attempt_move(SE, gm);
	if (delt.getX() < 0 && delt.getY() < 0)
		attempt_move(SW, gm);
		*/
}
