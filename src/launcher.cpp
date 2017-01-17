#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

//SNES it up!
const float FPS = 60;
const int GAME_W = 340;
const int GAME_H = 244;

int main(int argc, char **argv){

   al_init_font_addon(); // initialize the font addon
   al_init_ttf_addon();// initialize the ttf (True Type Font) addon


   ALLEGRO_DISPLAY *display = NULL;
   ALLEGRO_EVENT_QUEUE *event_queue = NULL;
   ALLEGRO_TIMER *timer = NULL;
   ALLEGRO_FONT *font = NULL;
   bool frame_drawn = false;

 
   if(!al_init()) {
      fprintf(stderr, "failed to initialize allegro!\n");
      return -1;
   }
 
   timer = al_create_timer(1.0 / FPS);
   if(!timer) {
      fprintf(stderr, "failed to create timer!\n");
      return -1;
   }
 
   ALLEGRO_MONITOR_INFO aminfo;   
   al_get_monitor_info(0 , &aminfo);   
   int desktop_width = aminfo.x2 - aminfo.x1 + 1;
   int desktop_height = aminfo.y2 - aminfo.y1 + 1;

   int SCREEN_W = GAME_W * (desktop_width / GAME_W);
   int SCREEN_H = GAME_H * (desktop_height / GAME_H);
 
   ALLEGRO_BITMAP *game_screen = al_create_bitmap(GAME_W, GAME_H);

   display = al_create_display(SCREEN_W, SCREEN_H);
   if(!display) {
      fprintf(stderr, "failed to create display!\n");
      al_destroy_timer(timer);
      return -1;
   }

   font = al_create_builtin_font();

   if (!font){
      fprintf(stderr, "Could not load font.\n");
      return -1;
   }

 
   event_queue = al_create_event_queue();
   if(!event_queue) {
      fprintf(stderr, "failed to create event_queue!\n");
      al_destroy_display(display);
      al_destroy_timer(timer);
      return -1;
   }
 
   al_register_event_source(event_queue, al_get_display_event_source(display));
 
   al_register_event_source(event_queue, al_get_timer_event_source(timer));
 
   al_start_timer(timer);



   while(1)
   {
      ALLEGRO_EVENT ev;
      al_wait_for_event(event_queue, &ev);
 
      if(ev.type == ALLEGRO_EVENT_TIMER) {
         al_set_target_bitmap(game_screen);
         al_clear_to_color(al_map_rgb(50,10,70));
         al_draw_text(font, al_map_rgb(255,0,0),GAME_W/2,32,ALLEGRO_ALIGN_CENTRE, "DUBSTEP ZOMBIES");
         frame_drawn = true;
      }
      else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
         break;
      }
 
      if(frame_drawn && al_is_event_queue_empty(event_queue)) {
        al_set_target_bitmap(al_get_backbuffer(display));
        al_draw_scaled_bitmap(game_screen,0,0, GAME_W, GAME_H,0,0,SCREEN_W,SCREEN_H, 0);
        al_flip_display();
      }
   }
 
   al_destroy_timer(timer);
   al_destroy_display(display);
   al_destroy_event_queue(event_queue);
   al_destroy_font(font);
 
   return 0;
}
