#include "titlescreen.h"

    GameState* TitleScreen::update_state()
    {
        // Let's just do a "PRESS ANY BUTTON TO START!"
        if(inputs_->getController(0)->newPress(Controller::Control.A))
        {
            return (new InGame(inputs_));
        }
        else return NULL;
    }

    void TitleScreen::draw_state(DrawUtils& drawUtils)
    {
        al_clear_to_color(al_map_rgb(50,10,70));
        drawUtils.drawCenteredString(255,0,0,drawUtils.GAME_W/2,32,"PRES H 2 Start!!1!");
    }

