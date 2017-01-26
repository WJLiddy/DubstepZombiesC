#ifndef DRAWUTILS_H
#define DRAWUTILS_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

class DrawUtils
{
private:
	// font used for the game. Just the basic system font.
	ALLEGRO_FONT *font_;
	// Game screen in NES coordinates (GAME_W * GAME_H)
	ALLEGRO_BITMAP *game_screen_;
	// Physical drawing screen.
	ALLEGRO_DISPLAY *display_;
	// Resolution of the game
	int screen_w_; 
	int screen_h_;

public:
	static const int GAME_W = 340;
	static const int GAME_H = 244;
	// IMPORTANT: Call drawing functions as if the game were in 340 / 244. flip() will take care of scaling!

    void beginDraw();
    void flip();
};
#endif 
