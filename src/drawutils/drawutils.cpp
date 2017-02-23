#include <string>
#include <iostream>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "drawutils.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
    DrawUtils::DrawUtils()
    {
    	// TODO: Check for errors if one of these failed
      // Initalize Allegro stuff
    	al_init_font_addon(); 
   		al_init_ttf_addon();
      al_init_image_addon();
		  al_init_primitives_addon();

   		ALLEGRO_MONITOR_INFO aminfo;   
  		al_get_monitor_info(0 , &aminfo);   
   		int desktop_width = aminfo.x2 - aminfo.x1 + 1;
   		int desktop_height = aminfo.y2 - aminfo.y1 + 1;

      // Calculate the screen size.
   		screen_w_ = GAME_W * (desktop_width / GAME_W);
   		screen_h_ = GAME_H * (desktop_height / GAME_H);
 
   		game_screen_ = al_create_bitmap(GAME_W, GAME_H);

   		display_ = al_create_display(screen_w_, screen_h_);

   		font_ = al_create_builtin_font();

		temp_ = al_create_bitmap(screen_w_, screen_h_);


		old_time = al_get_time();

		al_set_target_backbuffer(display_);

		ALLEGRO_TRANSFORM trans;
		al_identity_transform(&trans);
		al_scale_transform(&trans, screen_w_ / GAME_W, screen_h_ / GAME_H);
		al_use_transform(&trans);
    }

    void DrawUtils::beginDraw()
    {
	   //Used a transform- Not used!
      //al_set_target_bitmap(game_screen_);
      //al_clear_to_color(al_map_rgb(0,0,0));
    }

    void DrawUtils::flip()
    {
		double new_time = al_get_time();
		double delta = new_time - old_time;
		old_time = new_time;
		auto targ = std::to_string(1 / 60.0);
		auto delt = std::to_string(delta);
		targ.resize(5);
		delt.resize(5);
		drawStringCenter(al_map_rgba(1, 255, 1,128), GAME_W / 2, 10, "TARGET: " + targ);
		drawStringCenter(al_map_rgba(delta > .2 ? 255 : 0, delta < .2 ? 255 : 0, 1,128), GAME_W / 2, 20, "ACTUAL: " + delt);

      al_flip_display();
	  al_clear_to_color(al_map_rgb(0, 0, 0));
    }

	void DrawUtils::drawStringLeft(ALLEGRO_COLOR col, int x, int y, std::string s, bool bold)
    {
		drawStringHelper(col, x, y, s, bold, ALLEGRO_ALIGN_LEFT);
    }

	void DrawUtils::drawStringCenter(ALLEGRO_COLOR col, int x, int y, std::string s, bool bold)
	{
		drawStringHelper(col, x, y, s, bold, ALLEGRO_ALIGN_CENTRE);
	}

	void DrawUtils::drawStringRight(ALLEGRO_COLOR col, int x, int y, std::string s, bool bold)
	{
		drawStringHelper(col, x, y, s, bold, ALLEGRO_ALIGN_RIGHT);
	}

	void DrawUtils::drawStringHelper(ALLEGRO_COLOR col, int x, int y, std::string s, bool bold, int flag)
	{
		if (bold)
		{
			al_draw_text(font_, al_map_rgba_f(0, 0, 0,col.a ), x-1, y, flag, s.c_str());
			al_draw_text(font_, al_map_rgba_f(0, 0, 0, col.a), x, y-1, flag, s.c_str());
			al_draw_text(font_, al_map_rgba_f(0, 0, 0, col.a), x+1, y, flag, s.c_str());
			al_draw_text(font_, al_map_rgba_f(0, 0, 0, col.a), x, y+1, flag, s.c_str());
		}

		al_draw_text(font_,col, x, y, flag, s.c_str());
	}

    DrawUtils::~DrawUtils()
    {
    	al_destroy_font(font_);
    	al_destroy_display(display_);
      al_destroy_bitmap(game_screen_);
    }
