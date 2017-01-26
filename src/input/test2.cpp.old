//test.cpp
//A test program for controlls
#include <allegro5/allegro.h>
#include "controller.h"
#include <iostream>
#include "keyboard.h"
#include "keyboard.cpp"

int main(int argc, char** argv){
    al_init();//Allegro Initialization
    try{
    Keyboard test;//Create the test keyboard;
//    Joystick test2; //Create the test joystick
    test.setKey(RBUMPER, ALLEGRO_KEY_I);//Test setkey function    
    fprintf(stderr, "Driver for Keyboard\nHit any key to continue");    

   ALLEGRO_DISPLAY *display = NULL;
   ALLEGRO_EVENT_QUEUE *event_queue = NULL;
   ALLEGRO_TIMER *timer = NULL;

   timer = al_create_timer(1.0 / FPS);
   if(!timer) {
      fprintf(stderr, "failed to create timer!\n");
      return -1;
   }
   display = al_create_display(SCREEN_W, SCREEN_H);
   if(!display) {
      fprintf(stderr, "failed to create display!\n");
      al_destroy_timer(timer);
      return -1;
   }
    
   al_clear_to_color(al_map_rgb(255, 0, 255));
   al_set_target_bitmap(al_get_backbuffer(display));

   event_queue = al_create_event_queue();
   if(!event_queue) {
      fprintf(stderr, "failed to create event_queue!\n");
      al_destroy_bitmap(bouncer);
      al_destroy_timer(timer);
      return -1;
   }

   al_register_event_source(event_queue, al_get_display_event_source(display));
 
   al_register_event_source(event_queue, al_get_timer_event_source(timer));

   al_clear_to_color(al_map_rgb(0,0,0));
 
   al_flip_display();
 
   al_start_timer(timer);

    while(1)
   {
      ALLEGRO_EVENT ev;
      al_wait_for_event(event_queue, &ev);
 
      if(ev.type == ALLEGRO_EVENT_TIMER) {
         
      }
      else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
         break;
      }
 
      if(redraw && al_is_event_queue_empty(event_queue)) {
         
         al_clear_to_color(al_map_rgb(0,0,0));

         al_flip_display();
      }

    std::cout << "You Tapped the following controlls: \n";
    for (Controll index = A; index != END; ++index){
	if (test.tapped(index))
	    std::cout << StrControll(index) << "\n";	
    }
    std::cout << "You are holding down the following controlls: \n";    
    for (Controll index = A; index != END; ++index){
	if (test.pressed(index))
	    std::cout << StrControll(index) << "\n";
    }

    }

    catch (std::string err){
        std::cout << err;
    }


    
return 0;
}
