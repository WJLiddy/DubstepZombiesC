#include "gameobject.h"
#include "../utils/coord.h"

GameObject::GameObject(Coord c, int nw, int nh)
{
	coord = Coord(c.getX(),c.getY());
	w = nw;
	h = nh;
}
