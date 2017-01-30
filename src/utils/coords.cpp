#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

class Coords
{
	int x,y;
public:
	Coords(int,int);
	int setX(int);int setY(int);
	bool setCoords(int,int);

	int getX(){return x;}
	int getY(){return y;}

	bool equals(Coords);
	vector<Coords> getAdj4();
	vector<Coords> getAdj8();

	static double dist(Coords&, Coords&);
};

Coords::Coords(int xv, int yv)
{
	x = xv;y = yv;
}

int Coords::setX(int xv)
{
	x = xv;
	return x;
}

int Coords::setY(int yv)
{
	y = yv;
	return y;
}

bool Coords::setCoords(int xv, int yv)
{
	x = xv;y = yv;
	return true;
}

bool Coords::equals(Coords other)
{
	return x == other.getX() && y == other.getY();
}

vector<Coords> Coords::getAdj4()
{
	vector<Coords> res;
	vector<Coords> res2;
	res2.emplace_back(1,2);
	res.emplace_back(x,y+1);
	res.emplace_back(x,y-1);
	res.emplace_back(x+1,y);
	res.emplace_back(x-1,y);
	return res;
}

vector<Coords> Coords::getAdj8()
{
	vector<Coords> res(Coords::getAdj4());
	for (int i = 0; i < 4; i++)
	{
		res.emplace_back(x+((i&1)?1:-1),y+(((i>>1)&1)?1:-1));
	}
	return res;
}

ostream &operator<<(ostream &os, Coords c) { 
	return os << c.getX() << "," << c.getY() << "\n";
}

Coords operator+(Coords &a, Coords &b)
{
	int newx = a.getX()+b.getX();
	int newy = a.getY()+b.getY();
	return Coords(newx,newy);
}

Coords operator-(Coords &a, Coords &b)
{
	return Coords(a.getX()-b.getX(),a.getY()-b.getY());
}

double Coords::dist(Coords &a, Coords &b)
{
	return sqrt(pow(a.getX()-b.getX(),2)+pow(a.getY()-b.getY(),2));
}

/*
int main()
{
	Coords test(3,4);
	Coords org(0,0);
	vector<Coords> cs;
	for (int i = 0; i < 100; i++)	cs.emplace_back(i,i);
	auto adj = test.getAdj8();
	for_each(adj.begin(),adj.end(),[](Coords c){cout << c;});
	cout << org-test << org+test << Coords::dist(org,test) << "\n";
	return 0;
}
*/
