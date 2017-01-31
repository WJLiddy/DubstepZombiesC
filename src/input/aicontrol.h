//aicontrol.h
//For AI input
//Jacob Liddy

#ifndef AICONTROL_H
#define AICONTROL_H

#include "controller.h"

class AIcontrol : public Controller{
private:
    bool Vpressed[10];//The key is virtually pressed on the keyboard
    bool Vtapped[10];//The key is going to be virtually tapped on the keyboard. 
public:
    //Default Ctr:
    AIcontrol();
    
    //Tells you if a key is pressed for next update
    bool keyState(Control c){return Vpressed[c];}    

    //Mutators:
    void virtual_press(Control c){Vpressed[c] = true;} //Virtually Press key
    void virtual_unpress(Control c){Vpressed[c] = false;} //Virtually unpress key
    void virtual_tap(Control c){Vpressed[c] = true; Vtapped[c] = true;} 
    //^Automatically unpresses after update
    
    //Update:
    virtual void update();//Update AI controls, as if it was a keyboard
    //Useless setkey function declared so this is not an abstract data type:
    virtual void setKey(Control c, int garbage){}
};
#endif //AICONTROL_H

