#ifndef GAME_MAP
#define GAME_MAP

#include "common.h"
#include "coord.h"
#include "gameobject.h"

using namespace std;

class GameMap
{
	private:
	//2-way mapping
	unordered_map<Coord,unordered_set<GameObject> > gm_;
	unordered_map<string,unordered_set<GameObject> > layer_;

	void checkinsert(unordered_map<Coord,unordered_set<GameObject> > &,Coord,GameObject);
	void checkinsert(unordered_map<string,unordered_set<GameObject> > &,string,GameObject);
	
	public:
	GameMap();
	GameMap(vector<Coord>,GameObject);

	//puts the *entire* GO onto the map i.e. the rectangle, 
	//and the anchor coord i.e. the top-left into the layer
	void put(GameObject);
	void operator+=(GameObject);
	
	//inverse of put
	void remove(GameObject);
	void operator-=(GameObject);

	//remove->put
	void move(GameObject, Coord);
	
	//get what is on the coord
	vector<GameObject> get(int,int);
	vector<GameObject> get(Coord);
	
	//get where all the GOs of the parameter GO's type are placed
	//i.e. the top-left anchor
	vector<GameObject> collect(GameObject);
	
	vector<GameObject> operator[](Coord co);
	vector<GameObject> operator[](GameObject go);

	//does Coord have GameObject?
	bool has(GameObject, int, int);
	bool has(GameObject, Coord);
};

#endif
