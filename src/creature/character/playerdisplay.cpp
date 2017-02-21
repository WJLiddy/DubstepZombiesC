#include "playerdisplay.h"
#include "../../utils/coord.h"
#include "../../drawutils/drawutils.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

	//TODO: Get player ID, draw name at top of screen, draw items, draw 
	PlayerDisplay::PlayerDisplay(Player* p)
	{
		p_ = p;
		small_fill_ = al_load_bitmap("res/ui/bar/small/fill.png");
		small_segment_ = al_load_bitmap("res/ui/bar/small/segment.png");

		hungry_ = al_load_bitmap("res/ui/bar/hungry.png");
		thirsty_ = al_load_bitmap("res/ui/bar/thirsty.png");
		infected_ = al_load_bitmap("res/ui/bar/infected.png");

		fill_ = al_load_bitmap("res/ui/bar/fill.png");
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

	//range 0 to 0.99
	ALLEGRO_COLOR PlayerDisplay::bar_color_gradient(double alpha)
	{
		return  al_map_rgba_f(0, 0, alpha,alpha);
	}

	void PlayerDisplay::draw_small_energy_bar(int index, int x, int y)
	{
		//decay draw for every item.
		double alpha_mod = 1;
		if (energy_frame_ >  ENERGY_SUSTAIN_MAX)
		{
			alpha_mod = 1.0 - (((double)energy_frame_ - ENERGY_SUSTAIN_MAX) / ENERGY_DECAY_MAX);
		}
		auto alpha_color = al_map_rgba_f(alpha_mod, alpha_mod, alpha_mod, alpha_mod);


		//firstly, see if we are in the "stamina bar" segment
		if (index < p_->getEnergyCount())
		{
			if ((index+1) * p_->STAMINA_PER_ENERGY <= p_->getStaminaLevel())
			{
				//Full bar!
				al_draw_tinted_bitmap(small_fill_, al_map_rgba_f(0, 0, alpha_mod, alpha_mod) , x, y, 0);
			}

			if ((index * p_->STAMINA_PER_ENERGY) < p_->getStaminaLevel() && ((index + 1) * p_->STAMINA_PER_ENERGY) > p_->getStaminaLevel())
			{
				auto alpha = ((double)(p_->getStaminaLevel() % p_->STAMINA_PER_ENERGY)) / (double)p_->STAMINA_PER_ENERGY;
				auto color = bar_color_gradient(alpha);
				al_draw_tinted_bitmap(small_fill_, al_map_rgba_f(alpha_mod*color.r, alpha_mod*color.g, alpha_mod*color.b, alpha_mod*color.a), x, y, 0);
			}

			al_draw_tinted_bitmap(small_segment_, al_map_rgba_f(alpha_mod, alpha_mod, alpha_mod, alpha_mod), x, y, 0);

		}
	}

	//i repeated myself, deal
	void PlayerDisplay::draw_large_energy_bar(int index, int x, int y)
	{

		//firstly, see if we are in the "stamina bar" segment
		if (index < p_->getEnergyCount())
		{
			if ((index + 1) * p_->STAMINA_PER_ENERGY <= p_->getStaminaLevel())
			{
				//Full bar!
				al_draw_tinted_bitmap(fill_, al_map_rgba_f(0, 0, 1, 1), x, y, 0);
				al_draw_bitmap(segment_, x, y, 0);

			}

			else if ((index * p_->STAMINA_PER_ENERGY) < p_->getStaminaLevel() && ((index + 1) * p_->STAMINA_PER_ENERGY) > p_->getStaminaLevel())
			{
				auto alpha = ((double)(p_->getStaminaLevel() % p_->STAMINA_PER_ENERGY)) / (double)p_->STAMINA_PER_ENERGY;
				auto color = bar_color_gradient(alpha);
				al_draw_tinted_bitmap(fill_, color, x, y, 0);
				al_draw_bitmap(segment_, x, y, 0);

			} 
			else
			{
				al_draw_bitmap(segment_, x, y, 0);
			}
		}

		else if (index < p_->getEnergyCount() + p_->getEnergyMissingDueToThirst())
		{
			al_draw_tinted_bitmap(fill_, al_map_rgba_f(1, 0, 0, 1), x, y, 0);
			al_draw_bitmap(segment_, x, y, 0);
			al_draw_bitmap(thirsty_, x, y, 0);
		}
		else if (index < p_->getEnergyCount() + p_->getEnergyMissingDueToHunger() + p_->getEnergyMissingDueToThirst())
		{
			al_draw_tinted_bitmap(fill_, al_map_rgba_f(1, 0, 0, 1), x, y, 0);
			al_draw_bitmap(segment_, x, y, 0);
			al_draw_bitmap(hungry_, x, y, 0);
		}
		else
		{
			al_draw_tinted_bitmap(fill_, al_map_rgba_f(1, 0, 0, 1), x, y, 0);
			al_draw_bitmap(segment_, x, y, 0);
			al_draw_bitmap(infected_, x, y, 0);
		}

	}

	void PlayerDisplay::draw(DrawUtils& du, Coord& camera)
	{
		//SMALL ICON DRAWING

		//start drawing at bottom of char + 2
		int y_top = p_->getBottom() + 2;

		int left_icon_x;
		// set the leftmoset icon location. For an odd number:
		if ((p_->getEnergyCount() % 2) == 1)
		{
			int middle_icon_x = p_->getCoord().getX() + ((p_->player_size - small_icon_width) / 2);
			left_icon_x = middle_icon_x - ((p_->getEnergyCount() / 2)*small_icon_width);
		}
		else
		{
			//simply take the total width and subtract it from middle
			int middle_left = p_->getCoord().getX() + ((p_->player_size/2));
			left_icon_x = middle_left - (small_icon_width * (p_->getEnergyCount() / 2));
		}

		int icon_x = left_icon_x;
		for (int i = 0; i != p_->getEnergyCount(); i++)
		{
			draw_small_energy_bar(i, icon_x - camera.getX(), y_top + -camera.getY());
			icon_x = icon_x + (small_icon_width);
		}

		//HARDCODED LARGE ICON DRAWING
		du.drawStringLeft(al_map_rgb_f(1, 1, 1), 2, 2, "Jacket", true);

		for (int i = 0; i != p_->BASE_ENERGY; i++)
		{
			draw_large_energy_bar(i, 2 + i*(large_icon_width), 12);
		}
	}


