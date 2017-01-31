#ifndef INGAME_H
#define INGAME_H

#include "../input/inputs.h"
#include "gamestate.h"
#include "../drawutils/drawutils.h"

class InGame : public GameState
{
public:	
	InGame(Inputs* inputs) : GameState(inputs) {}
  
    GameState* update_state();
    
    void draw_state(DrawUtils& drawUtils);
};
#endif
