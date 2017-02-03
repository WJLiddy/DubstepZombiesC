#include "gameobject.h"
#include "../utils/coord.h"

GameObject::GameObject(Coord c, string type, unordered_set<Coord> body_, string uuid)
{
	co_ = c;
	body_ = b;
	type_ = type;
	uuid_ = uuid;
}

bool operator==(const GameObject& other) const
{
	return uuid() == other.uuid();
}

ostream &operator<<(ostream &os, GameObject go)
{
	return os << go.getCoord() << "," << go.getType() << "," << go.getName() << "\n";
}
