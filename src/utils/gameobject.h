#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "common.h"
#include "../utils/coord.h"

class GameObject
{
	public:
	//public coords because I don't care about information hiding lmao
	//TODO remove default init
	Coord coord = Coord(0,0);
	int w;
	int h;
	//Also a width and a height.
	GameObject(Coord, int, int);
};

#endif
