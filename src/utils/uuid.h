#include "common.h"
using namespace std;

class UUID
{
        private:
        mt19937 rd_;

        public:
        UUID(string seed);
        string getUUID();
	long long gettime();
};

