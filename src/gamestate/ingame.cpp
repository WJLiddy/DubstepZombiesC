#include "gamestate.h"
#include "ingame.h"


    GameState* InGame::update_state()   
    {
        return NULL;
    }

    
    void InGame::draw_state(DrawUtils& drawUtils)  
    {
        al_clear_to_color(al_map_rgb(50,10,70));
        drawUtils.drawCenteredString(255,0,0,drawUtils.GAME_W/2,32,"U R PLAYIN GAEM");
    }