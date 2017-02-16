//keyboard.cpp

//Functions from keyboard class
#include "keyboard.h"
#include <fstream> //Files 'n shit

/**********************************
    Default constructor:
	Installs keyboard driver, 
    checks for failure, throws an
    error if so. 

    TODO: Make default keys?
**********************************/


    bool Keyboard::usedKeys[ALLEGRO_KEY_MAX] = {0};//all keys are not used


/************************************
    setKey:
	Maps the key to an unused key 
    on the keyboard. Throws an int 
    error if the key is used.

    ________________________________
	Parameters:
    Controll c  ... the Enum being set 
    int keycode ... the key it is being
			mapped to
    _________________________________
	Errors:
    *)1... if the key is used by another 
	    keyboard
    *)2... if the key is not allowed
	    such as ESC or 
    __________________________________
    
************************************/

void Keyboard::setKey(Control c, int keycode){
    //TODO: ADD ERROR 2 (KEY IS NOT ALLOWED)
    std::string errMsg;
    errMsg.append(al_keycode_to_name(keycode));
    errMsg.append(" is in use\n");
    if (usedKeys[keycode])
	throw errMsg;
    if (KeyMap[c] != -1) //Initialized Keyboard controller
	usedKeys[KeyMap[c]] = false;//Old Key no longer in use
    KeyMap[c] = keycode;//Map New key
    usedKeys[keycode] = true; //New key is used.
}


/************************************
    Update:
	Updates the state of the 
    keyboar. Not sure of parameters,
    after all, I am a n00b to allegro
    It MAY require the keyboard state
    but I will TODO mess with it.
************************************/

void Keyboard::update(){
    ALLEGRO_KEYBOARD_STATE state; //Get state of keyboard
    al_get_keyboard_state(&state);

    for(Control index = A; index < END; next(index))//loop through each key
    {
	justPressed[index] = false;//Reset "justpressed" keys

	if ( al_key_down(&state, KeyMap[index]) ){//If the key is pressed
	    press(index);//Press it
	} else {
	    unPress(index);
	}
    }
}

/********************************************************1337*********
    void save(string): Save keyboard state to a file under a username.
Saves in the text file keybindings.txt, which load will search out of 
*********************************************************************/

void Keyboard::save(std::string user) const{
    //Make sure a user was specified in order to save
    if (usr != "NO_USR"){
	std::fstream file;
	//Open the file for read(IN), write(OUT), and always APPend to the 
	//end of the file
	file.open("keybindings.txt", std::fstream::in |std::fstream::out | std::fstream::app);
    

	file.close();
    }
}

/**********************************************************************
    load(string) : Load the key bindings of a user. If those key bindings don't exist, then create a user and save the default bindings under that user.
**********************************************************************/

void Keyboard::load(std::string user){
    if (user == "NO_USR"){
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
    } else {

        std::fstream file;
        //Open the file for read(IN), write(OUT), and always APPend to the 
        //end of the file
        file.open("keybindings.txt", std::fstream::in |std::fstream::out | std::fstream::app);


        file.close();
    }
}
