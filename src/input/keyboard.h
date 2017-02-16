//Keyboard Class:
//  Derived from the controller class,
//  for keyboard input

//Jacob Liddy

#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "controller.h"
#include <list> //Static list of keys used
#include <string> //User

class Keyboard : public Controller{
private:
    static bool usedKeys[ALLEGRO_KEY_MAX];//One for each key
			//Allegro key max should be 118
    int KeyMap[10]; // The map to the controlls
public:
    Keyboard(std::string user = "NO_USR") : Controller()
{       
    if (!al_install_keyboard()){
	fprintf(stderr, "Failed to install keyboard!\n");
	return;
    }
    //Initialized keys
    KeyMap[0] = -1;
    KeyMap[1] = -1;
    KeyMap[2] = -1;
    KeyMap[3] = -1;
    KeyMap[4] = -1;
    KeyMap[5] = -1;
    KeyMap[6] = -1;
    KeyMap[7] = -1;
    KeyMap[8] = -1;
    KeyMap[9] = -1;

    load(user);//Load the keys - Default "NO_USR"
}
    virtual void update();//Update keyboard
    virtual void setKey(Control, int); //Bind a key
    virtual void save(std::string user) const; //Save some key bindings
    virtual void load(std::string user); //Load some key bindings
};

#endif //KEYBOARD_H
