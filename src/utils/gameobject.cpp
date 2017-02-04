#include "gameobject.h"
#include "../utils/coord.h"
#include "../utils/uuid.h"

GameObject::GameObject(Coord c, string type, unordered_set<Coord> b)
{
	co_ = c;
	body_ = b;
	type_ = type;
	uuid_ = uuidgen.getUUID();
}

bool GameObject::operator==(const GameObject& other) const
{
	return uuid_ == other.uuid();
}