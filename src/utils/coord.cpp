#include "coord.h"

Coord::Coord()
{
	x = 0; y = 0;
}

Coord::Coord(int xv = 0, int yv = 0)
{
	x = xv;y = yv;
}

int Coord::setX(int xv)
{
	x = xv;
	return x;
}

int Coord::setY(int yv)
{
	y = yv;
	return y;
}

bool Coord::setCoord(int xv, int yv)
{
	x = xv;y = yv;
	return true;
}

bool Coord::operator==(const Coord &other) const
{
	return x == other.getX() && y == other.getY();
}

Coord Coord::operator+(const Coord &other) const
{
	int newx = getX() + other.getX();
	int newy = getY() + other.getY();
	return Coord(newx, newy);
}

Coord Coord::operator-(const Coord &other) const
{
	return Coord(getX() - other.getX(), getY() - other.getY());
}



vector<Coord> Coord::getAdj4()
{
	vector<Coord> res;
	vector<Coord> res2;
	res2.emplace_back(1,2);
	res.emplace_back(x,y+1);
	res.emplace_back(x,y-1);
	res.emplace_back(x+1,y);
	res.emplace_back(x-1,y);
	return res;
}

vector<Coord> Coord::getAdj8()
{
	vector<Coord> res(Coord::getAdj4());
	for (int i = 0; i < 4; i++)
	{
		res.emplace_back(x+((i&1)?1:-1),y+(((i>>1)&1)?1:-1));
	}
	return res;
}

ostream &operator<<(ostream &os, Coord c) { 
	return os << c.getX() << "," << c.getY() << "\n";
}



double Coord::dist(Coord &a, Coord &b)
{
	return sqrt(pow(a.getX()-b.getX(),2)+pow(a.getY()-b.getY(),2));
}

unordered_set<Coord> Coord::generateRect(int w, int h)
{
	unordered_set<Coord> set;
	for (int i = 0; i != w; i++)
	{
		for (int j = 0; j != h; j++)
		{
			set.emplace(Coord(i, j));
		}
	}
	return set;
}


/*
int main()
{
	Coord test(3,4);
	Coord org(0,0);
	vector<Coord> cs;
	for (int i = 0; i < 100; i++)	cs.emplace_back(i,i);
	auto adj = test.getAdj8();
	for_each(adj.begin(),adj.end(),[](Coord c){cout << c;});
	cout << org-test << org+test << Coord::dist(org,test) << "\n";
	unordered_map<Coord,int> tm;
	tm[test] = 7;
	cout << tm[test] << endl;
	return 0;
}
*/
