#include "inputs.h"

    Inputs::Inputs()
    {
        controllers_ = new std::vector<Controller*>();
        for(int i = 0; i != PLAYERCOUNT; i++)
        {
            controllers_.push_back(NULL);
        }
    }

    void Inputs::setPlayerInput(int playernumber, Controller* c)
    {
        delete(controllers_[playernumber])
        controllers_[playernumber] = c;
    }

    Controller* Inputs::getController(int playernumber)
    {
        return controllers_[playernumber];
    }

    void update()
    {
        for (int i=0; i < controllers_.size; i++) 
        {
            controllers_[i].update();
        }
    }
}

#endif 
