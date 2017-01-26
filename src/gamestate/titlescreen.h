#ifndef TITLESCREEN_H
#define TITLESCREEN_H

#include "../input/inputs.h"
#include "gamestate.h"

class TitleScreen : public GameState
{
public:	// Pass player inputs between states, but that's about the only thing.
	TitleScreen(Inputs* inputs);
    GameState* update_state();
    void draw_state(DrawUtils *drawUtils);
};
#endif
