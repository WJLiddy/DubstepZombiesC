#ifndef MALLDRAW_H
#define MALLDRAW_H

//Drawing information about the game map.
class MallDraw
{
private:
    ALLEGRO_BITMAP* base_;
    ALLEGRO_BITMAP* always_;
public:
	void draw_base(Coords,drawUtils&);
	void draw_scan(Coords,drawUtils&);
};
#endif 
