#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <bitset>

#define ID_MASK 0x00000008	// µ×ÈýÎ»Îª1
#define ID_BIT	5

using namespace std;

int main(){
	int userId = 4;
	bitset<16> bs(userId);
	cout << bs << endl;
	cout << bs.reset(2) << endl;
	userId = userId | ID_MASK << ID_BIT;
	bitset<16> * pbs = new bitset<16>(userId);
	cout << * pbs << endl;
	delete pbs;
	system("pause");
	return 0;
}