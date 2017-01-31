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
	DrawUtils();
	~DrawUtils();

	// This function is used at the start of every "state" draw function to flip the buffer. 
    void beginDraw();

    // Physically draws the bitmap to the screen. Again, this is only used by the state.
    void flip();

    // CALL THE BELOW FUNCTIONS BETWEEN beginDraw() and flip().
    
    // Draws a centered string on the screen at r,g,b,x,y,string.  
    void drawCenteredString(int, int, int, int, int, std::string);
};
#endif 
