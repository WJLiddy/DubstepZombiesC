#include "gamemap.h"

GameMap::GameMap()
{
	gm_.clear();
	layer_.clear();
}

GameMap::GameMap(vector<Coord> collisions, GameObject colObj)
{
	gm_.clear();
	layer_.clear();
	for (Coord co:collisions)
	{
		gm_[co].insert(colObj);
		layer_[colObj.getType()].insert(colObj);
	}
}

void GameMap::put(int x, int y, GameObject go)
{
	GameMap::put(Coord(x,y),go);
}

void GameMap::put(Coord co, GameObject go)
{
	
	for (Coord c : go.getBody())
		gm_[go.getCoord()+c].insert(go);
	layer_[go.getType()].insert(go);
}

void GameMap::remove(GameObject go)
{
	for (Coord c: go.getBody())
	{
		gm_[go.getCoord()+c].erase(go);
	}
	layer_[go.getType()].erase(go);
}

void GameMap::move(GameObject go, Coord co)
{
	GameMap::remove(go);
	GameMap::put(co,go);
}


unordered_set<GameObject> GameMap::get(int x, int y)
{
	return GameMap::get(Coord(x,y));
}

unordered_set<GameObject> GameMap::get(Coord co)
{
	return gm_[co];
}

unordered_set<GameObject> GameMap::collect(GameObject go)
{
	return layer_[go.getType()];
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

