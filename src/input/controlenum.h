//controlEnum.h
//Jacob's First namespace
//Contains enum used for controlls

#ifndef CONTROL_H
#define CONTROL_H

namespace controlEnum
{
    enum Control{A = 0, B, X, Y, UP, DOWN, LEFT, RIGHT, LBUMPER, RBUMPER, END};

            //TODO: Jacob: Let me shoewyou a shortcut for this
    std::string StrControl(Control c){
        std::string returnStr;
        switch (c){
            case A:
                returnStr = "A";
                break;
            case B:
                returnStr = "B";
                break;
            case X:
                returnStr = "X";
                break;
            case Y:
                returnStr = "Y";
                break;
            case UP:
                returnStr = "Up";
                break;
            case DOWN:
                returnStr = "Down";
                break;
            case LEFT:
                returnStr = "Left";
                break;
            case RIGHT:
                returnStr = "Right";
                break;
            case LBUMPER:
                returnStr = "Left Bumper";
                break;
            case RBUMPER:
                returnStr = "Right Bumper";
                break;
            }            
	    return returnStr;
        }
}

#endif //CONTROL_H
