#include "gamemap.h"
#include "coord.h"

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

void GameMap::put(GameObject go)
{
	
	for (Coord c : go.getBody())
	{
		gm_.at(go.getCoord()+c).insert(go);
	}
	layer_[go.getType()].insert(go);
}

void GameMap::remove(GameObject go)
{
	for (Coord c: go.getBody())
	{
		gm_.at(go.getCoord()+c).erase(go);
	}
	layer_[go.getType()].erase(go);
}

void GameMap::move(GameObject go, Coord co)
{
	GameMap::remove(go);
	go.setCoord(co);
	GameMap::put(go);
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


int main(int argc, char **argv) 
{
	GameMap gm;
	unordered_set<Coord> body;
	body.insert(Coord(1, 1));
	GameObject test1(Coord(1,1), "test1", body);
	gm.put(test1);
	return 0;
}


