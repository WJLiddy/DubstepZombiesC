#ifndef COORD_H
#define COORD_H

#include "common.h"

using namespace std;

class Coord
{
        int x,y;
public:
		Coord();
        Coord(int,int);
        int setX(int);int setY(int);
        bool setCoord(int,int);

        int getX() const{return x;}
        int getY() const{return y;}

        bool operator==(const Coord&) const;
        vector<Coord> getAdj4();
        vector<Coord> getAdj8();

        static double dist(Coord&, Coord&);
};

namespace std
{
	template<>
	struct hash<Coord>
	{
		size_t operator()(const Coord& co) const
		{
			return ((hash<int>()(co.getX()))^(hash<int>()(co.getY())));
		}
	};
}

Coord operator+(Coord &a, Coord &b)
{
	int newx = a.getX() + b.getX();
	int newy = a.getY() + b.getY();
	return Coord(newx, newy);
}

Coord operator-(Coord &a, Coord &b)
{
	return Coord(a.getX() - b.getX(), a.getY() - b.getY());
}
		
#endif