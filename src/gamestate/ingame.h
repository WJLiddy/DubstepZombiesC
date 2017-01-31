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
    
    void draw_state(DrawUtils& drawUtils)  
    {
        al_clear_to_color(al_map_rgb(50,10,70));
        drawUtils.drawCenteredString(255,0,0,drawUtils.GAME_W/2,32,"U R PLAYIN GAEM");
    }
};
#endif
