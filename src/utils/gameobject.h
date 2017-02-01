#include "common.h"
#include "../utils/coord.h"

class GameObject
{
	public:
	//public coords because I don't care about information hiding lmao
	Coord coord;
	//Also a width and a height.
	GameObject(Coord, int, int);
};

