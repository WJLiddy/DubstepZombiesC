#ifndef RENDEROBJECT_H
#define RENDEROBJECT_H

#include "common.h"
#include "../utils/coord.h"
#include "../utils/gameobject.h"
#include "../utils/uuidz.h"

class RenderObject : public GameObject
{

	public:
		RenderObject(Coord c, string s, unordered_set<Coord> body) : GameObject(c, s, body) {}
		//Draw relative to camera
		virtual void draw(Coord&) = 0;
		virtual int getBottom() = 0;

		static bool lower(RenderObject* struct1, RenderObject* struct2)
		{
			return (struct1->getBottom() < struct2->getBottom());
		}
};




#endif
