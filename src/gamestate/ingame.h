#ifndef INGAME_H
#define INGAME_H

#include "../input/inputs.h"
#include "gamestate.h"
#include "../drawutils/drawutils.h"
#include "../utils/coord.h"
#include "../mall/malldraw.h"
#include "../mall/mallobject.h"
#include "../character/player.h"

class InGame : public GameState
{
private:
    //Top left pixel of the map that is displayed at (0,0).
    Coord camera_ = Coord(100,100);
    MallDraw* md_;
	Player p_;
	GameMap m_;
	unordered_set<Coord> collide_;
	bool debug_;
	std::vector<MallObject> mall_objects_;

public:	
	InGame(Inputs*);
  
    GameState* update_state();

    void draw_state(DrawUtils& drawUtils);

};

#endif
