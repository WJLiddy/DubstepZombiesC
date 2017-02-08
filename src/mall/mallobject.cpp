#include "mallobject.h"
#include <allegro5/allegro.h>
#include "../utils/renderobject.h"

	MallObject::MallObject(std::vector<ALLEGRO_BITMAP*> frames, std::vector<int> frame_times, unordered_set<Coord> body, Coord position, int h) : RenderObject(position, "MALL_STATIC_OBJECT", body)
	{
		frames_ = frames;
		frame_times_ = frame_times;
		frame_ptr_ = 0;
		frame_time_left_ = frame_times_.at(0);
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

	void MallObject::draw(Coord& camera)
	{
		al_draw_bitmap(frames_.at(frame_ptr_), getCoord().getX() - camera.getX(), getCoord().getY() - camera.getY(), 0);
	}

	int MallObject::getBottom()
	{
		return getCoord().getY() + h_;
	}
