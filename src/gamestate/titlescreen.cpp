#include "titlescreen.h"


    Gamestate* update(); // P U R E  V I R T U A L  F U N C T I O N S
    void draw();

    Titlescreen::Titlescreen(Inputs* inputs)
    {
        inputs_ = inputs;
    }

    void Titlescreen::update()
    {
        //Nothing to do here, yet!
    }


    void update(DrawUtils* drawutils)
    {
        for (int i=0; i < controllers_.size; i++) 
        {
            controllers_[i].update();
        }
    }
}

#endif 
