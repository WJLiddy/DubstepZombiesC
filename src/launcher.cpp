#include <stdio.h>
#include <allegro5/allegro.h>
#include "gamestate/gamestate.h"
#include "gamestate/titlescreen.h"
#include "drawutils/drawutils.h"
#include "input/keyboard.h"

const float FPS = 60;

int main(int argc, char **argv){

   ALLEGRO_EVENT_QUEUE *event_queue = NULL;
   ALLEGRO_TIMER *timer = NULL;
   bool frame_drawn = false;

   //TODO: double check for memleaks, and if these initializers really every throw a false value
   if(!al_init()) {
      fprintf(stderr, "failed to initialize allegro!\n");
      return -1;
   }
 
   timer = al_create_timer(1.0 / FPS);
   if(!timer) {
      fprintf(stderr, "failed to create timer!\n");
      return -1;
   }
  
   event_queue = al_create_event_queue();
   if(!event_queue) {
      fprintf(stderr, "failed to create event_queue!\n");
      al_destroy_timer(timer);
      return -1;
   }
 
   // Necessary? al_register_event_source(event_queue, al_get_display_event_source(display));

   al_register_event_source(event_queue, al_get_timer_event_source(timer));
 
   al_start_timer(timer);

   // Load programatically from a file later, but for now,
   Inputs *inputs = new Inputs();
   //Default keys
   inputs->setPlayerInput(0, new Keyboard());
   DrawUtils *drawUtils = new DrawUtils();
   GameState *gameState = new TitleScreen(inputs);

   while(1)
   {
      ALLEGRO_EVENT ev;
      al_wait_for_event(event_queue, &ev);
 
      if(ev.type == ALLEGRO_EVENT_TIMER) {
         GameState* next_state = gameState->update();
         if(next_state)
         {
            delete(gameState);
            gameState = next_state;
         }
         frame_drawn = true;
      }
      else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
         break;
      }
 
      if(frame_drawn && al_is_event_queue_empty(event_queue)) {
         gameState->draw(drawUtils);
         frame_drawn = false;
      }
   }
 
   al_destroy_timer(timer);
   al_destroy_event_queue(event_queue);
   return 0;
}
