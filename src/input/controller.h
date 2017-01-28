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


class Controller{
public:
	//I'm going to put this enum inside this class to keep it out of the global namespace
	enum Control{A = 0, B, X, Y, UP, DOWN, LEFT, RIGHT, LBUMPER, RBUMPER, END};

protected:
    bool isPressed[10]; // True If key is pressed 
    bool justPressed[10];

    void press(Control c); // c IS pressed & held down
    void newPress(Control c); // c was just pressed downs
    void unPress(Control c);//c was let go
public:
	

	//TODO: Jacob: Let me shoewyou a shortcut for this
	std::string StrControl(Control c){
	    std::string returnStr;
	    switch (c){
		case A:
		    returnStr = "A";
		    break;
		case B:
		    returnStr = "B";
		    break;
		case X:
		    returnStr = "X";
		    break;
		case Y:
		    returnStr = "Y";
		    break;
		case UP:
		    returnStr = "Up";
		    break;
		case DOWN:
		    returnStr = "Down";
		    break;
		case LEFT:
		    returnStr = "Left";
		    break;
		case RIGHT:
		    returnStr = "Right";
		    break;
		case LBUMPER:
		    returnStr = "Left Bumper";
		    break;
		case RBUMPER:
		    returnStr = "Right Bumper";
		    break;
		}
	    return returnStr;
	}

	// Does this have to go here or can it go in the cpp file?
    Controller(){for(int i = 0; i < 10; i++) isPressed[i] = false;}

    virtual void update() = 0;
    virtual void setKey(Control, int) = 0;
    //Tapped returns if the controll has just been pressed
    bool tapped(Control c) const{return justPressed[c];}
    //Pressed returns if the controll is pressed down
    bool pressed(Control c) const{return isPressed[c];}
};
#endif //CONTROLLER_H
