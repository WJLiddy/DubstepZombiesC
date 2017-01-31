#include "gamestate.h"

    GameState::GameState(Inputs* inputs)
    {
        inputs_ = inputs;
    }

    void GameState::draw(DrawUtils& drawUtils)
    {
        //Set the backbitmap
        drawUtils.beginDraw();
        //Let the state draw what it wants
        draw_state(drawUtils);
        //Flip it. 
        drawUtils.flip();
    }

    GameState* GameState::update()
    {
    	inputs_->update();
    	return update_state();
    }
