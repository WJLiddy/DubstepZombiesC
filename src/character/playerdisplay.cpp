#include "playerdisplay.h"
#include "../utils/coord.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

	PlayerDisplay::PlayerDisplay(Player* p)
	{
		p_ = p;
	}

	// Get the state of the player, and make any updates we need. called between draws
	void PlayerDisplay::update()
	{
		//first: check if we should reset the clock because stamina was lost
		//also: if stamina is not moving and not full
		if (p_->getStaminaLevel() < last_stamina || (p_->getStaminaLevel() == last_stamina && p_->getStaminaLevel() != p_->getMaxStamina()))
		{
			energy_frame_ = 0;
		}

		last_stamina = p_->getStaminaLevel();

		if (energy_frame_ < ENERGY_DECAY_MAX + ENERGY_SUSTAIN_MAX)
			energy_frame_++;

	}

	void PlayerDisplay::draw_energy_bar(int index, int x, int y)
	{
		al_draw_filled_rectangle(x, y, x + icon_width, y + 6, al_map_rgb((128 * index) % 256, (90 * index) % 256, (32 * index) % 256));
	}

	void PlayerDisplay::draw(Coord& camera)
	{
		//don't worry about this expression
		int y_top = p_->getBottom();
		int middle_icon_x = p_->getCoord().getX() + ((p_->player_size - icon_width) / 2);
		int left_icon_x = middle_icon_x - ((p_->getBaseEnergy() / 2)*icon_width);
		int icon_x = left_icon_x;
		for (int i = 0; i != p_->getBaseEnergy(); i++)
		{
			draw_energy_bar(i, icon_x - camera.getX(), y_top + 2 - camera.getY());
			icon_x = icon_x + (icon_width);
		}
	}


