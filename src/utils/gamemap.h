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
	
	public:
	GameMap();
	GameMap(vector<Coord>,GameObject);

	//puts the *entire* GO onto the map i.e. the rectangle, 
	//and the anchor coord i.e. the top-left into the layer
	void put(int,int,GameObject);
	void put(Coord,GameObject);
	
	//inverse of put
	void remove(GameObject);

	//remove->put
	void move(GameObject, Coord);
	
	//get what is on the coord
	unordered_set<GameObject> get(int,int);
	unordered_set<GameObject> get(Coord);
	
	//get where all the GOs of the parameter GO's type are placed
	//i.e. the top-left anchor
	unordered_set<GameObject> collect(GameObject);
};
