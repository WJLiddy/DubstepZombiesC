#ifndef TITLESCREEN_H
#define TITLESCREEN_H

#include "../input/inputs.h"
#include "gamestate.h"
#include "../drawutils/drawutils.h"

class TitleScreen : public GameState
{
public:	
	TitleScreen(Inputs* inputs) : GameState(inputs) {}
  
    GameState* update_state();
    
    void draw_state(DrawUtils& drawUtils);
};
#endif
