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

    ALLEGRO_EVENT_QUEUE *event_queue = NULL; 
	event_queue = al_create_event_queue();

    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_create_display(300,200);
    fprintf(stderr, "Driver for Keyboard\nHit any key to continue");    
    ALLEGRO_EVENT ev;
    al_wait_for_event(event_queue, &ev);
    al_wait_for_event(event_queue, &ev);
    test.update();
    fprintf(stderr, "\nYou hit ");
    std::cout << al_keycode_to_name(ev.keyboard.keycode) << "\n";
    std::cout << "You held down the following controlls: \n";
    
    for (Controll index = A; index != END; ++index){
	if (test.tapped(index))
	    std::cout << StrControll(index) << "\n";
    }
    }
    catch (std::string err){
        std::cout << err;
    }


    
return 0;
}
