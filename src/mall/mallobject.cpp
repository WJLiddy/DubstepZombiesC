#include "mallobject.h"
#include <allegro5/allegro.h>

	MallObject::MallObject(std::vector<ALLEGRO_BITMAP*> frames, std::vector<int> frame_times, Coord c, int w, int h) : GameObject(c, w, h)
	{
		frames_ = frames;
		frame_times_ = frame_times;
		frame_ptr_ = 0;
		frame_time_left_ = frame_times_.at(0);
	}

	void MallObject::tick()
	{
		frame_time_left_--;
		if(!frame_time_left_)
		{
			frame_ptr_ = (frame_ptr_ + 1 % frames_.size());
			frame_time_left_ = frame_times_[frame_ptr_];
		}
	}

	//implemenation may change here depending on ted's "map" class. Draws relative to camera.
	void draw(Coord& camera)
	{
		//todo

	}
