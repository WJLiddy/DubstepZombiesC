#include "common.h"

class GameObject
{
	public:
	//public coords because I don't care about information hiding lmao
	Coords coords;
	//Also a width and a height.
	GameObject(Coords, int, int);
};

