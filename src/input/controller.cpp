//Incudes functions for pure abstract class Controller

#include "controller.h"
/****************************
    press:
    Checks if a key has 
    been pressed before. if it 
    has, do nothing. If it has 
    not, run newPress.
****************************/

void Controller::press(Control c){
    if (isPressed[c] == false)
    newPress(c);
}

/*****************************
    newPress:
    Update key state, and
    since it was just pressed 
    update justPressed
*****************************/    

void Controller::newPress(Control c){
    justPressed[c] = true;
    isPressed[c] = true;
}

/*****************************
    unPress:
    Update key state, make 
    sure the key state is 
    off
****************************/

void Controller::unPress(Control c){ 
    isPressed[c] = false; 
}