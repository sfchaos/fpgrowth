#include <iostream>
#include <string>
#include "../lib/FPgrowth.hpp"

using namespace std;

int main()
{
	string fn = "../data/test.dat";
	//string fn = "../data/retail.dat";
	unsigned int minsup = 4;
	FPgrowth fpg(minsup);
	fpg.readTran(fn);
	fpg.construct();

	return 0;
}
