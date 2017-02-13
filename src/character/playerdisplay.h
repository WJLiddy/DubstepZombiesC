#ifndef PLAYERDISPLAY_H
#define PLAYERDISPLAY_H
#include <allegro5/allegro.h>
#include "player.h"
#include "../utils/coord.h"

//Drawing information on top of the player.
class PlayerDisplay
{
	friend class Player;
private:
	Player* p_;
	// 0 - DECAY; DECAY - SUSTAIN;
	int energy_frame_ = 0;
	//friend class
	int last_stamina = 0;
	const int ENERGY_DECAY_MAX = 30;
	const int ENERGY_SUSTAIN_MAX = 30;
	const int icon_width = 6;

	ALLEGRO_BITMAP* energy_;
	ALLEGRO_BITMAP* food_;
	ALLEGRO_BITMAP* water_;
	ALLEGRO_BITMAP* infection_;

	void draw_energy_bar(int, int, int);

public:
	PlayerDisplay(Player* p);
	// Get the state of the player, and make any updates we need. called between draws
	void update();
	void draw(Coord& Camera);
};
#endif 
