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
    Keyboard() : Controller()
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

    //Default Keys
    setKey(A, ALLEGRO_KEY_H);
    setKey(B, ALLEGRO_KEY_J);
    setKey(X, ALLEGRO_KEY_N);
    setKey(Y, ALLEGRO_KEY_M);
    setKey(UP, ALLEGRO_KEY_W);
    setKey(DOWN, ALLEGRO_KEY_S);
    setKey(LEFT, ALLEGRO_KEY_A);
    setKey(RIGHT, ALLEGRO_KEY_D);
    setKey(RBUMPER, ALLEGRO_KEY_U);
    setKey(LBUMPER, ALLEGRO_KEY_Y);

}
    virtual void update();//Update keyboard
    virtual void setKey(Control, int);
};

#endif //KEYBOARD_H
