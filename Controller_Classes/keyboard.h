//Keyboard Class:
//  Derived from the controller class,
//  for keyboard input

//Jacob Liddy

#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "controller.h"
#include <list> //Static list of keys used

class Keyboard : public Controller{
private:
    static bool usedKeys[ALLEGRO_KEY_MAX];//One for each key
			//Allegro key max should be 118
    int KeyMap[10]; // The map to the controlls
public:
    Keyboard();
    virtual void update();//Update keyboard
    virtual void setKey(Controll, int);
};
    bool Keyboard::usedKeys[ALLEGRO_KEY_MAX] = {0};//all keys are not used

#endif //KEYBOARD_H
