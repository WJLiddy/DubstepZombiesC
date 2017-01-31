//aicontrol.h
//Functions for AIcontrol class
//Jacob Liddy

//TODO remove "#include 'file.h'"'s in .cpp files
#include "aicontrol.h"

/************************************
    Default ctr
	Set all keystates to off(false)
*************************************/
AIcontrol::AIcontrol(){
    for(int i=0; i < 10; i++){
	Vpressed[i] = false;
	Vtapped[i] = false;
    }
}

/**********************************
    void pressKey(Controll c)
	Make state of key pressed
**********************************/
void AIcontrol::update(){

    for(Controll index = A; index < END; ++index)//loop through each key
    {
        justPressed[index] = false;//Reset "justpressed" keys

        if ( Vpressed[index]) {//If the key is virtually pressed
            press(index);//Press it(for REAL)
        } else {
            unPress(index);//Unpress it(for REAL)
        }

	if (Vtapped[index]){//If the key was only ment to be tapped - 
	    virtual_unpress(index); //Unpress it!
	    Vtapped[index] = false; //Don't tap it next time.
	}	
    }
}
	
