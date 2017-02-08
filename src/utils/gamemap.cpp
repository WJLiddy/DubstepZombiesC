#include "gamemap.h"
#include "coord.h"

void GameMap::checkinsert(unordered_map<Coord,unordered_set<GameObject> > &tar, Coord co, GameObject go)
{
	if (!tar.count(co))
		tar[co]=unordered_set<GameObject>();
	tar[co].insert(go);
}

void GameMap::checkinsert(unordered_map<string,unordered_set<GameObject> > &tar, string type, GameObject go)
{
	if (!tar.count(type))
		tar[type]=unordered_set<GameObject>();
	tar[type].insert(go);
}

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
		checkinsert(gm_,co,colObj);
		checkinsert(layer_,colObj.getType(),colObj);
	}
}

void GameMap::put(GameObject go)
{
	for (Coord c : go.getBody())
	{
		checkinsert(gm_,go.getCoord()+c,go);
	}
	checkinsert(layer_,go.getType(),go);
}

void GameMap::operator+=(GameObject go)
{
	GameMap::put(go);
}

void GameMap::remove(GameObject go)
{
	try
	{
		for (Coord c: go.getBody())
		{
			gm_.at(go.getCoord()+c).erase(go);
		}
		layer_[go.getType()].erase(go);
	}
	catch (const out_of_range& oor)
	{
		cerr<<"The gameobject doesn't exist in the map"<<oor.what()<<"\n";
	}
}

void GameMap::operator-=(GameObject go)
{
	GameMap::remove(go);
}

void GameMap::move(GameObject go, Coord co)
{
	GameMap::remove(go);
	go.setCoord(co);
	GameMap::put(go);
}

vector<GameObject> GameMap::get(int x, int y)
{
	return GameMap::get(Coord(x,y));
}

vector<GameObject> GameMap::get(Coord co)
{
	if (!gm_.count(co))
		return vector<GameObject>();
	auto res = gm_[co];
	return vector<GameObject>(res.begin(),res.end());
}

vector<GameObject> GameMap::operator[](Coord co)
{
	return GameMap::get(co);
}

vector<GameObject> GameMap::collect(GameObject go)
{
	if (!layer_.count(go.getType()))
		return vector<GameObject>();
	auto res = layer_[go.getType()];
	return vector<GameObject>(res.begin(),res.end());
}

vector<GameObject> GameMap::operator[](GameObject go)
{
	return GameMap::collect(go);
}

bool GameMap::has(GameObject go, int x, int y)
{
	return GameMap::has(go,Coord(x,y));
}

bool GameMap::has(GameObject go, Coord co)
{
	if (!gm_.count(co))
		return false;
	auto res = gm_[co];
	return res.find(go)!=res.end();
}


//see the showcase section of usages of this class
int main(int argc, char **argv) 
{
	//making test objects
	GameMap gm;
	unordered_set<Coord> body;
	Coord testco(1,1);
	body.insert(testco);
	GameObject test1(Coord(0,0), "test1", body);

	//usage showcase
	cout << testco << endl;
	cout << test1 << endl;
	//put
	gm+=test1;
	//notice that here, the test1 GO is anchored at (0,0), 
	//yet its body doesn't cover (0,0) as it only has (1,1)
	cout << gm.has(test1, test1.getCoord()) << endl;
	cout << gm.has(test1,1,1) << endl;
	//collect
	cout << gm[test1][0] << endl;
	//get
	cout << gm[Coord(1,1)][0] << endl;
	//remove
	gm-=test1;
	cout << gm.has(test1,1,1) << endl;
	return 0;
}

