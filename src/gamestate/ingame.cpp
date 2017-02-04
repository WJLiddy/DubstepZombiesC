#include "gamestate.h"
#include "ingame.h"
#include "../utils/coord.h"
#include "../mall/mallparser.h"
#include "../mall/malldraw.h"
#include "../utils/gamemap.h"

	// Set up our camera, load in bitmap, etc.
	InGame::InGame(Inputs* inputs) : GameState(inputs) 
	{
        // Parse the mall map, collect the MapObjects, MapDraw, and set of collide coords (to be forward to ted's map class.) 
        MallParser mp = MallParser::parse("res/maps/test/");
        md_ = mp.mallDraw;
		mall_objects_ = mp.mallObjects;
		
		GameObject gm(Coord(), "MALL_STATIC_BASE_COLLIDE", mp.collide);

		GameMap m = GameMap();
	}

    GameState* InGame::update_state()   
    {
		for (auto &value : mall_objects_) 
		{

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

		// VERY NAIVE IMPL: Should sort here, later, rather that (H * P) I can do this in P log P.
		for (int y = 0; y != md_->height; y++)
		{

			for (auto &value : mall_objects_)
			{
				if (value.coord.getY() + value.h == y)
				{
					value.draw(camera_);
					if (debug_)
						value.drawDebug(camera_);
				}
			}
			if(p.coord.getY() + p.h == y)
				p.draw(camera_);
		}

        md_->draw_always(camera_);
		if (debug_)
			md_->draw_debug_collide(camera_);
    }

