#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "common.h"
#include "../utils/coord.h"
#include "../utils/gameobject.h"
#include "../utils/uuidz.h"
class GameObject
{
	private:
	Coord co_;
	string type_;
	unordered_set<Coord> body_;
	string uuid_;
	string name_;


	public:
	//Hardcoded seed
	static UUIDZ uuidgen;

	GameObject(Coord, string, unordered_set<Coord>);
	
	string getType() const { return type_; }
	
	unordered_set<Coord> getBody() { return body_; }
	
	Coord getCoord() const { return co_; }
	void setCoord(Coord c) { co_ = c; }
	
	string uuid() const{ return uuid_; }
	
	void setName(string name) { name_ = name; }
	string getName() const { return name_ == ""?"unnamed":name_; }

	bool operator==(const GameObject&) const;

	operator string() const
	{
		return to_str();
	}

	string to_str() const
	{
		return getName()+":<"+getType()+","+uuid()+", at:"+getCoord().to_str()+">";
	}
};

ostream &operator<<(ostream&, GameObject);

namespace std
{
	template<>
	struct hash<GameObject>
	{
		size_t operator()(const GameObject& go) const
		{
			hash<string> hasher;
			return hasher(go.uuid());
		}
	};
}

#endif
