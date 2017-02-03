#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "common.h"
#include "../utils/coord.h"

class GameObject
{
	//>"Gotta follow good coding practice"
	//>"Everything is public"
	//>mfw
	private:
	Coord co_;
	string type_;
	unordered_set<Coord> body_;
	string uuid_;
	string name_;

	public:
	GameObject(Coord, string, unordered_set<Coord>,string);
	
	string getType() {return type_;}
	
	unordered_set<Coord> getBody() {return body_};
	
	Coord getCoord() {return co_;}
	void setCoord(Coord c) {co_ = c;}
	
	string uuid() {return uuid_;}
	
	void setName(string name){name_ = name;}
	string getName(){return name_;}

	bool operator==(const GameObject&) const;
};

namespace std
{
	template<>
	struct hash<GameObject>
	{
		size_t operator()(const GameObject& go) const
		{
			return hash<string>(go.uuid());
		}
	};
}

#endif
