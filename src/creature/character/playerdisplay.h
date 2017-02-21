#ifndef PLAYERDISPLAY_H
#define PLAYERDISPLAY_H
#include <allegro5/allegro.h>
#include "player.h"
#include "../../utils/coord.h"
#include "../../drawutils/drawutils.h"

//Drawing information on top of the player.
class PlayerDisplay
{
	friend class Player;
private:
	Player* p_;
	// 0 - DECAY; DECAY - SUSTAIN;
	int energy_frame_ = 0;
	int last_stamina = 0;

	const double MOVE_SPEED = 0.9;
	const int ENERGY_DECAY_MAX = 120;
	const int ENERGY_SUSTAIN_MAX = 120;
	
	const int small_icon_width = 6;
	const int large_icon_width = 16;

	ALLEGRO_BITMAP* small_fill_;
	ALLEGRO_BITMAP* small_segment_;

	ALLEGRO_BITMAP* fill_;
	ALLEGRO_BITMAP* segment_;
	ALLEGRO_BITMAP* hungry_;
	ALLEGRO_BITMAP* thirsty_;
	ALLEGRO_BITMAP* infected_;


	void draw_small_energy_bar(int, int, int);
	void draw_large_energy_bar(int, int, int);
	ALLEGRO_COLOR bar_color_gradient(double);
public:
	PlayerDisplay(Player* p);
	// Get the state of the player, and make any updates we need. called between draws
	void update();
	void draw(DrawUtils& du,Coord& Camera);
};
#endif 
