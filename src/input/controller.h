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

enum Controll{A = 0, B, X, Y, UP, DOWN, LEFT, RIGHT, LBUMPER, RBUMPER, END};

//Prefix operator for controll Enum
Controll operator ++(Controll &id)
{
   Controll currentID = id;

   if ( END < id + 1 ) id = A;
   else id = static_cast<Controll>( id + 1 );

   return (currentID);
}

//The function StrControll turns a Controll
//into it's string name for display purpose
std::string StrControll(Controll c){
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

class Controller{
protected:
    bool isPressed[10]; // True If key is pressed 
    bool justPressed[10];

    void press(Controll c); // c IS pressed & held down
    void newPress(Controll c); // c was just pressed downs
    void unPress(Controll c);//c was let go
public:
    Controller(){for(int i = 0; i < 10; i++) isPressed[i] = false;}

    virtual void update() = 0;
    virtual void setKey(Controll, int) = 0;//Pure virtual function for setting keys  
    //Tapped returns if the controll has just been pressed
    bool tapped(Controll c) const{return justPressed[c];}
    //Pressed returns if the controll is pressed down
    bool pressed(Controll c) const{return isPressed[c];}
};
#endif //CONTROLLER_H
