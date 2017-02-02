#ifndef MALL_OBJECT_H
#define MALL_OBJECT_H

#include "../utils/common.h"
#include "../utils/gameobject.h"
#include "../utils/coord.h"
#include <allegro5/allegro.h>

class MallObject : public GameObject
{
private:
	std::vector<ALLEGRO_BITMAP*> frames_;
	ALLEGRO_BITMAP* debug_;
	std::vector<int> frame_times_; 
	int frame_ptr_;
	int frame_time_left_;
public:
	
	MallObject(std::vector<ALLEGRO_BITMAP*>, std::vector<int>, ALLEGRO_BITMAP*, Coord, int, int);
	void tick();
	//implemenation may change here depending on ted's "map" class. Draws relative to camera.
	void draw(Coord&);

	void drawDebug(Coord&);
};

#endif