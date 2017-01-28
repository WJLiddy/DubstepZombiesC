#ifndef TITLESCREEN_H
#define TITLESCREEN_H

#include "../input/inputs.h"
#include "gamestate.h"
#include "../drawutils/drawutils.h"

class TitleScreen : public GameState
{
public:	
	// Pass player inputs between states, but that's about the only thing.
	// TODO I need to seperate these classes.
	TitleScreen(Inputs* inputs) : GameState(inputs) {}
  
    GameState* update_state()
    {
        //Nothing to do here! No state update, so just return a null pointer.
        return NULL;
    }

    void draw_state(DrawUtils* drawUtils)
    {
        al_clear_to_color(al_map_rgb(50,10,70));
        drawUtils->drawCenteredString(255,0,0,drawUtils->GAME_W/2,32,"DUBSTEP ZOMBIES");
    }

};
#endif
