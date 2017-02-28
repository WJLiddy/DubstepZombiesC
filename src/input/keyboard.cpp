//keyboard.cpp

//Functions from keyboard class
#include "keyboard.h"
#include <fstream> //Files 'n stuff
#include <queue> //Que for holding file stuff
#include <sstream> //Convert int to string using ostreamstring

using std::string;
using std::ostringstream;

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

void Keyboard::save(std::string user){
    //Make sure a user was specified in order to save
    if (usr != "NO_USR"){
	//Set up current controlls in a string to be put into a file.
	string current_controls = "    ";
	for (Control index = A; index < END; next(index)){
	    current_controls.append(StrControl(index));
	    current_controls.append(": ");
	    
	    /* Convert int -> ostringstream -> string */
	    ostringstream converter; //Convert an int to str
	    converter << KeyMap[index];
	    current_controls.append(converter.str());
	    //TODO append control here
	    current_controls.append("; ");
	}

	std::fstream file;
	//Open the file for read(IN)
	file.open("keybindings.txt", std::fstream::in | std::fstream::app);

	bool found = false; //Was the record in the file?
	std::queue<string> file_q;//File queue - to temporary hold cont of file
        string line;
        string old_controls = "";
        while (getline(file, line)){
	    file_q.push(line);

            if (line == user){
		found = true;//The controls are found
                getline(file, old_controls);
		file_q.push(current_controls);//Replace controls
                break; //Break from the for loop
            }
        }
	
	//Since the line was broken early
	while (getline(file,line)){
	    file_q.push(line);
	}
	file.close(); // And finished

	//Open file for output - and clear it before so(trunc)
	std::ofstream redoFile("keybindings.txt", std::ios::out | std::ios::trunc);

	while (!file_q.empty()){
	    redoFile << file_q.front() << std::endl;
	    file_q.pop(); //Remove line put in
	}
	/* If record DNE, add it */
	if (found == false){ 
	    redoFile << std::endl;
	    redoFile << user << std::endl;
	    redoFile << current_controls << std::endl;
	}

	//All done
	redoFile.close();
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
	
	string line;
	string controls = "";
	while (getline(file, line)){
	    if (line == user){
		getline(file, controls);
		break; //Break from the for 
	    }
	}
	//Look at controls, and figure out which controls are which

        file.close();
    }
}
