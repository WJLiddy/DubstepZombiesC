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
		GameMap m_;
		GameObject gm(Coord(0,0), "MALL_STATIC_BASE_COLLIDE", mp.collide);
		m_.put(gm);
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

		p_.update(*inputs_->getController(0),m_);
		camera_.setX(p_.getCoord().getX() - DrawUtils::GAME_W / 2 + (p_.player_size / 2));
		camera_.setY(p_.getCoord().getY() - DrawUtils::GAME_H / 2 + (p_.player_size / 2));
        return NULL;
    }

    
    void InGame::draw_state(DrawUtils& drawUtils)  
    {
		md_->draw_base(camera_);

		std::vector<RenderObject*> to_render;

		for (auto value : mall_objects_)
		{
			to_render.push_back(&value);
		}

		to_render.push_back(&p_);
		
		std::sort(std::begin(to_render), std::end(to_render), RenderObject::lower);


		for (auto value : to_render)
		{
			value->draw(camera_);
			//draw colission info (TODO)
			//if (debug_)
				//value.drawDebug(camera_);
		}
        md_->draw_always(camera_);
		//draw colission info (TODO)
		//if (debug_)
			//md_->draw_debug_collide(camera_);
    }

