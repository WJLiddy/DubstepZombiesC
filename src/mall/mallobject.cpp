#include "mallobject.h"
#include <allegro5/allegro.h>

	MallObject::MallObject(std::vector<ALLEGRO_BITMAP*> frames, std::vector<int> frame_times, ALLEGRO_BITMAP* debug, Coord c, int w, int h) : GameObject(c, w, h)
	{
		debug_ = debug;
		frames_ = frames;
		frame_times_ = frame_times;
		frame_ptr_ = 0;
		//frame_time_left_ = frame_times_.at(0);
	}

	void MallObject::tick()
	{
		frame_time_left_ = frame_time_left_ - 1;

		if(frame_time_left_ <= 0)
		{
			frame_ptr_ = ((frame_ptr_ + 1) % frames_.size());

			frame_time_left_ = frame_times_[frame_ptr_];
		}
	}

	//implemenation may change here depending on ted's "map" class. Draws relative to camera.
	void MallObject::draw(Coord& camera)
	{
		al_draw_bitmap(frames_.at(frame_ptr_), coord.getX() - camera.getX(), coord.getY() - camera.getY(), 0);

	}

	void MallObject::drawDebug(Coord& camera)
	{
		al_draw_bitmap(debug_, coord.getX() - camera.getX(), coord.getY() - camera.getY(), 0);
	}
