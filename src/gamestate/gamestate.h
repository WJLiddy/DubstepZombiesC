#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "../input/inputs.h"
#include "../drawutils/drawutils.h"

class GameState
{
protected:
	Inputs* inputs_;
public:
	// Pass player inputs between states, but that's about the only thing.
	GameState(Inputs* inputs) {
		inputs_ = inputs;
	}
	// Returns the next state to run update() and draw() on.
    virtual GameState* update_state() = 0; // P U R E  V I R T U A L  F U N C T I O N S
    // Use DrawUtils and allegro in this function to draw what you need to draw. Everything will automatically be scaled to the screen resolution.
    virtual void draw_state(DrawUtils* drawUtils) = 0; // P U R E  V I R T U A L  F U N C T I O N S
	void draw(DrawUtils* DrawUtils);
	GameState* update();
};
#endif 
