#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "Persion.h"

using namespace std;

int main(){
	Persion p = Persion();
	Persion * pp = &p ;
	cout << pp->getName() << endl;
	cout << (*pp).getName() << endl;

	system("pause");
	return 0;
}