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
		collide_ = mp.collide;
		mall_objects_ = mp.mallObjects;
	}

    GameState* InGame::update_state()   
    {
		for (auto value : mall_objects_) {
			value.tick();
		}
		
		if (inputs_->getController(0)->tapped(Controller::A))
		{
			debug_ = !debug_;
		}
		p.update(*inputs_->getController(0),collide_);
		camera_.setX(p.coord.getX() - DrawUtils::GAME_W / 2);
		camera_.setY(p.coord.getY() - DrawUtils::GAME_H / 2);
        return NULL;
    }

    
    void InGame::draw_state(DrawUtils& drawUtils)  
    {
        md_->draw_base(camera_);
		p.draw(camera_);
        md_->draw_always(camera_);
		md_->draw_debug_collide(camera_);
    }