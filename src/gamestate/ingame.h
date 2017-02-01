#ifndef INGAME_H
#define INGAME_H

#include "../input/inputs.h"
#include "gamestate.h"
#include "../drawutils/drawutils.h"
#include "../utils/coord.h"
#include "../mall/malldraw.h"

class InGame : public GameState
{
private:
    //Top left pixel of the map that is displayed at (0,0).
    Coord camera_ = Coord(100,100);
    MallDraw* md_;

public:	
	InGame(Inputs*);
  
    GameState* update_state();

    void draw_state(DrawUtils& drawUtils);

};
#endif
