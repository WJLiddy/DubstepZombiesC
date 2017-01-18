//Joystick Class:
//  A subclass of the controller, for 
//  SNES controller or other joysticks
//Jacob Liddy

#ifndef JOYSTICK_H
#define JOYSTICK_H
#include "controller.h"

class Joystick : public controller{
private:
    int JoyMap[10]; // Map from controll to joy
public:
    Joystick();
    virtual void setKey(Controll, int);

};
#endif //JOYSTICK_H 
