#include "gamemap.h"

GameMap::GameMap()
{
	gm_.clear();
}

GameMap::GameMap(vector<Coord> collisions, GameObject collisionObject)
{
	gm_.clear();
	for (Coord co:collisions)
		gm_[co].push_back(collisionObject);
}

void GameMap::put(int x, int y, GameObject go)
{
	GameMap::put(Coord(x,y),go);
}

void GameMap::put(Coord co, GameObject go)
{
	gm_[co].push_back(go);
}

vector<GameObject> GameMap::get(int x, int y)
{
	return GameMap::get(Coord(x,y));
}

vector<GameObject> GameMap::get(Coord co)
{
	return gm_[co];
}

/**
int main()
{
	GameMap gm;
	GameObject go;
	gm.put(Coord(3,4),go);
	gm.get(Coord(3,4));
	gm.get(3,5);
	return 0;
}
*/

