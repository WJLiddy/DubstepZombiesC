#include "gamestate.h"
#include "ingame.h"
#include "../utils/coord.h"
#include "../mall/mallparser.h"
#include "../mall/malldraw.h"

	// Set up our camera, load in bitmap, etc.
	InGame::InGame(Inputs* inputs) : GameState(inputs) 
	{
        // Parse the mall map, collect the MapObjects, MapDraw, and set of collide coords (to be forward to ted's map class.) 
        MallParser mp = MallParser::parse("res/maps/test/");
        md_ = mp.mallDraw;
	}

    GameState* InGame::update_state()   
    {
        return NULL;
    }

    
    void InGame::draw_state(DrawUtils& drawUtils)  
    {
        al_clear_to_color(al_map_rgb(50,10,70));
        md_->draw_base(camera_);
        drawUtils.drawCenteredString(255,0,0,drawUtils.GAME_W/2,32,"U R PLAYIN GAEM");
        md_->draw_always(camera_);
    }