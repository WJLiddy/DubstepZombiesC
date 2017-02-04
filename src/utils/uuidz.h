#ifndef UUIDZ_H
#define UUIDZ_H

#include "common.h"
using namespace std;

class UUIDZ
{
        private:
        mt19937 rd_;

        public:
        UUIDZ(string seed);
        string getUUID();
		long long gettime();
};
#endif

