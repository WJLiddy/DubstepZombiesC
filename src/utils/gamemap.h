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
	unordered_map<Coord,unordered_set<string> > gm_;
	unordered_map<string,unordered_set<string> > layer_;

	void checkinsert(unordered_map<Coord,unordered_set<string> > &,Coord,GameObject&);
	void checkinsert(unordered_map<string,unordered_set<string> > &,string,GameObject&);
	
	unordered_map<string,shared_ptr<GameObject> >ref_;
	vector<shared_ptr<GameObject> > getref(unordered_set<string>);


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
	void move(GameObject&, Coord);
	
	//get what is on the coord
	vector<shared_ptr<GameObject> > get(int,int);
	vector<shared_ptr<GameObject> > get(Coord);
	
	//get where all the GOs of the parameter GO's type are placed
	//i.e. the top-left anchor
	vector<shared_ptr<GameObject> > collect(GameObject);
	
	//collect by name. 
	vector<shared_ptr<GameObject>> collect(string name);

	vector<shared_ptr<GameObject> > operator[](Coord);
	vector<shared_ptr<GameObject> > operator[](GameObject);

	//does Coord have GameObject?
	bool has(GameObject, Coord);
	bool has(GameObject, int, int);

	//dereference the object pointer
	GameObject getobj(shared_ptr<GameObject> gop){return *gop;} //hue
};

#endif
