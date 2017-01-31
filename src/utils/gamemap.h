#include "common.h"
#include "coord.h"
#include "gameobject.h"

using namespace std;

class GameMap
{
	private:
	unordered_map<Coord,vector<GameObject> > gm_;
	
	public:
	GameMap();
	GameMap(vector<Coord>,GameObject);

	void put(int,int,GameObject);
	void put(Coord,GameObject);
	vector<GameObject> get(int,int);
	vector<GameObject> get(Coord);

};
