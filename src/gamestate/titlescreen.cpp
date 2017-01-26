#include "titlescreen.h"

    TitleScreen::TitleScreen(Inputs *inputs)
    {
        GameState(Inputs* inputs);
    }

    GameState *TitleScreen::update_state()
    {
        //Nothing to do here! No state update, so just return a null pointer.
        return NULL;
    }

    void TitleScreen::draw_state(DrawUtils *drawUtils)
    {
        al_clear_to_color(al_map_rgb(50,10,70));
        drawUtils->drawCenteredString(255,0,0,drawUtils->GAME_W/2,32,"DUBSTEP ZOMBIES");
    }
}

#endif 
