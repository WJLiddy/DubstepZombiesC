#include "mapobject.h"

	MallObject::MapObject(std::vector<ALLEGRO_BITMAP*> frames, std::vector<int> frame_times, Coords c, int w, int h) : Controller(c, w,h)
	{
		frames_ = frames;
		frame_times = frame_times_;
		frame_ptr_ = 0;
		frame_time_left_ = frame_times_[0];
	}

	void MallObject::tick()
	{
		frame_time_left--;
		if(!frame_time_left_)
		{
			frame_ptr = (frame_ptr + 1 % frames.length());
			frame_time_left_ = frame_times[frame_ptr_];
		}
	}

	//implemenation may change here depending on ted's "map" class. Draws relative to camera.
	void draw(Coords camera)
	{
		//todo

	}