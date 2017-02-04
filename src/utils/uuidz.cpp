#include "uuidz.h"

UUIDZ::UUIDZ()
{
	string seed = to_string(gettime());
	seed_seq s (seed.begin(),seed.end());
	rd_.seed(s);
}

//modified version of UUIDv4
string UUIDZ::getUUID()
{
	stringstream ss;
	ss << hex << UUIDZ::gettime();
	string res = ss.str();
	res.replace(15,1,"-");
	res.insert(12,"1");
	res.insert(12,"-");
	res.insert(8,"-");
	res+="4";
	ss.str(string());
	ss << hex;
	for (int i = 0; i < 15; i++)
		ss << (rd_()%16);
	string rnd = ss.str();
	rnd.insert(3,"-");
	res+=rnd;
	return res;
}

long long UUIDZ::gettime()
{
	using namespace std::chrono;
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	return (long long)t1.time_since_epoch().count();
}

/*
int main()
{
	UUID gen(to_string(gen.gettime()));
	cout << gen.getUUID()<<endl;
}*/
