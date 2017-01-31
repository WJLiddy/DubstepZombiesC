#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "../input/inputs.h"
#include "../drawutils/drawutils.h"

class GameState
{
protected:
	Inputs* inputs_;
public:

    // Need the player inputs used in this gamestate.
    GameState(Inputs* inputs);

    // Some methods to take care of state things in the background. update draw and inputs, etc.
    void draw(DrawUtils& drawUtils);
    GameState* update();

	// Execute the state, and return the state to execute on the next frame. // P U R E  V I R T U A L  
    virtual GameState* update_state() = 0;
    // Use DrawUtils and allegro in this function to draw what you need to draw on an update.
    virtual void draw_state(DrawUtils& drawUtils) = 0; 

};
#endif 
