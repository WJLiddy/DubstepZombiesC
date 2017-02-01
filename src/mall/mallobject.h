#include "../utils/common.h"
#include "../utils/gameobject.h"
#include "../utils/coord.h"

class MallObject : GameObject
{
private:
	std::vector<ALLEGRO_BITMAP*> frames_;
	std::vector<int> frame_times_; 
	int frame_ptr_;
	int frame_time_left_;
public:
	
	MallObject(std::vector<ALLEGRO_BITMAP*>, std::vector<int> , Coord, int, int);
	void tick();
	//implemenation may change here depending on ted's "map" class. Draws relative to camera.
	void draw(Coord);
};

