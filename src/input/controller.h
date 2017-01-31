//controller.h

//Controller Class:
//This virtual class will allow controller subclasses to be 
//created for different types of controller
//
//Also contains enum class Controll
//

//Jacob Liddy
#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <stdio.h>
#include <allegro5/allegro.h>
#include <string>

#include "controlenum.h"

using namespace controlEnum;

class Controller{
    //Enum moved into its own namespace: controlEnum
protected:
    bool isPressed[10]; // True If key is pressed 
    bool justPressed[10];

    void press(Control c); // c IS pressed & held down
    void newPress(Control c); // c was just pressed downs
    void unPress(Control c);//c was let go
public:
	
	// Does this have to go here or can it go in the cpp file? 
	//(Jacob)Response: No - I moved it
    Controller();

    virtual void update() = 0;
    virtual void setKey(Control, int) = 0;
    //Tapped returns if the controll has just been pressed
    bool tapped(Control c) const{return justPressed[c];}
    //Pressed returns if the controll is pressed down
    bool pressed(Control c) const{return isPressed[c];}
};
#endif //CONTROLLER_H
