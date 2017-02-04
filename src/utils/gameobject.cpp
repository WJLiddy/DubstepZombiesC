#include "gameobject.h"
#include "../utils/coord.h"
#include "../utils/uuidz.h"

//based on clock
UUIDZ GameObject::uuidgen;

GameObject::GameObject(Coord c, string type, unordered_set<Coord> b)
{
	co_ = c;
	body_ = b;
	type_ = type;
	uuid_ = GameObject::uuidgen.getUUID();
}

bool GameObject::operator==(const GameObject& other) const
{
	return uuid_ == other.uuid();
}