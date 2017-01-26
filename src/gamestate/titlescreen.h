#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "input/inputs.h"

class TitleScreen : public Gamestate
{
private:
	Inputs* inputs_;
public:
	// Pass player inputs between states, but that's about the only thing.
	Gamestate(Inputs* inputs);
    Gamestate* update();
    void draw_state(DrawUtils* drawutils);
};
#endif
