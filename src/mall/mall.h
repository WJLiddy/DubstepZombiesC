#ifndef MAP_H
#define MAP_H

//Drawing information about the game map.
class MapDraw
{
private:
    ALLEGRO_BITMAP* base_;
    ALLEGRO_BITMAP* always_;
public:
	void draw_base(Coords,drawUtils&);
	void draw_scan(Coords,drawUtils&);
};
#endif 
