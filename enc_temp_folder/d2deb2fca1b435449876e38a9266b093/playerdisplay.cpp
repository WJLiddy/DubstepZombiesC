#include "playerdisplay.h"
#include "../utils/coord.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

	PlayerDisplay::PlayerDisplay(Player* p)
	{
		p_ = p;
		fill_ = al_load_bitmap("res/ui/bar/fill.png");
		hungry_ = al_load_bitmap("res/ui/bar/hunger.png");
		thirsty_ = al_load_bitmap("res/ui/bar/thirst.png");
		infected_ = al_load_bitmap("res/ui/bar/infected.png");
		segment_ = al_load_bitmap("res/ui/bar/segment.png");

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
		//firstly, see if we are in the "stamina bar" segment
		if (index < p_->getEnergyCount())
		{
			if ((index+1) * p_->STAMINA_PER_ENERGY < p_->getStaminaLevel())
			{
				//Full bar!
				al_draw_bitmap(fill_, x, y, 0);
			}

			if ((index * p_->STAMINA_PER_ENERGY) < p_->getStaminaLevel() && ((index + 1) * p_->STAMINA_PER_ENERGY) > p_->getStaminaLevel())
			{
				double alpha = ((double)(p_->getStaminaLevel() % p_->STAMINA_PER_ENERGY)) / (double)p_->STAMINA_PER_ENERGY;
				std::cout << alpha << endl;
				std::cout << p_->getStaminaLevel() << endl;
				al_draw_tinted_bitmap(fill_, al_map_rgba_f(alpha, alpha, alpha, alpha), x, y, 0);
			}

		}
		else if (index <  p_->getEnergyCount() + p_->getEnergyMissingDueToThirst())
		{
			al_draw_tinted_bitmap(fill_, al_map_rgba_f(0, 0, 0, 0.5), x, y, 0);
			al_draw_bitmap(thirsty_, x, y, 0);
		}
		else if (index <  p_->getEnergyCount() + p_->getEnergyMissingDueToThirst() + p_->getEnergyMissingDueToHunger())
		{
			al_draw_tinted_bitmap(fill_, al_map_rgba_f(0, 0, 0, 0.5), x, y, 0);
			al_draw_bitmap(hungry_, x, y, 0);
		}
		else
		{
			al_draw_tinted_bitmap(fill_, al_map_rgba_f(0, 0, 0, 0.5), x, y, 0);
			al_draw_bitmap(infected_, x, y, 0);
		}

		al_draw_bitmap(segment_, x, y, 0);
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


