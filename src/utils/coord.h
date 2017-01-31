#include "common.h"

using namespace std;

class Coord
{
        int x,y;
public:
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
		
