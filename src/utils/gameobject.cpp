#include "gameobject.h"
#include "../utils/coord.h"

GameObject::GameObject(Coord c, int nw, int nh)
{
	coord = c;
	w = nw;
	h = nh;
}
