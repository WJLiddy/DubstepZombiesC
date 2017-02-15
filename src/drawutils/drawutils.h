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

	ALLEGRO_BITMAP* temp_;
	// Resolution of the game
	int screen_w_; 
	int screen_h_;
	
	void DrawUtils::drawStringHelper(ALLEGRO_COLOR col, int x, int y, std::string s, bool bold, int flag);

public:
	static const int GAME_W = 340;
	static const int GAME_H = 244;
	ALLEGRO_DISPLAY *display_;
	double old_time;
	DrawUtils();
	~DrawUtils();

	// This function is used at the start of every "state" draw function to flip the buffer. 
    void beginDraw();

    // Physically draws the bitmap to the screen. Again, this is only used by the state.
    void flip();

    // CALL THE BELOW FUNCTIONS BETWEEN beginDraw() and flip().
   

	void drawStringLeft(ALLEGRO_COLOR col, int x, int y, std::string s, bool bold = false);

	void drawStringCenter(ALLEGRO_COLOR col, int x, int y, std::string s, bool bold = false);

	void drawStringRight(ALLEGRO_COLOR col, int x, int y, std::string s, bool bold = false);


};
#endif 
