#include "inputs.h"

    Inputs::Inputs()
    {
        //TODO: Read up on if this is good style.
        controllers_ = new std::vector<Controller*>();
        for(int i = 0; i != PLAYERCOUNT; i++)
        {
            controllers_->push_back(NULL);
        }
    }

   void Inputs::setPlayerInput(int playernumber, Controller* c)
    {
        delete((*controllers_)[playernumber]);
        (*controllers_)[playernumber] = c;
    }

    Controller* Inputs::getController(int playernumber)
    {
        return (*controllers_)[playernumber];
    }

    void Inputs::update()
    {
        for (int i=0; i < controllers_->size(); i++) 
        {
            if(!(*controllers_)[i])
            {
                continue;
            }
            ((*controllers_)[i])->update();
        }
    }

    //TODO Destructor.

