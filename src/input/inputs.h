#ifndef INPUTS_H
#define INPUTS_H

#include "controller.h"
#include <vector>

class Inputs 
{
private:
     std::vector<Controller*> controllers_; 
public:
	static const int PLAYERCOUNT = 3;
    void setPlayerInput(int playernumber, Controller* c);
    Controller* getController(int playernumber);
    void update();
};

#endif 
