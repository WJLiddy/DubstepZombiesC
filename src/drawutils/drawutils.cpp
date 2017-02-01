#include <string>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "drawutils.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>

    DrawUtils::DrawUtils()
    {
    	// TODO: Check for errors if one of these failed
      // Initalize Allegro stuff
    	al_init_font_addon(); 
   		al_init_ttf_addon();
      al_init_image_addon();

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
    }

    void DrawUtils::beginDraw()
    {
    	al_set_target_bitmap(game_screen_);
      al_clear_to_color(al_map_rgb(0,0,0));
    }

    void DrawUtils::flip()
    {
      al_set_target_bitmap(al_get_backbuffer(display_));
      al_draw_scaled_bitmap(game_screen_,0,0, GAME_W, GAME_H,0,0,screen_w_,screen_h_, 0);
      al_flip_display();
    }

    void DrawUtils::drawCenteredString(int r, int g, int b, int x, int y, std::string s)
    {
    	al_draw_text(font_, al_map_rgb(r,g,b),x,y,ALLEGRO_ALIGN_CENTRE, s.c_str());
    }

    DrawUtils::~DrawUtils()
    {
    	al_destroy_font(font_);
    	al_destroy_display(display_);
      al_destroy_bitmap(game_screen_);
    }
