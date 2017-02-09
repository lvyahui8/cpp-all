#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

enum Jar_Type {CUP = 8,PINT = 7,QUART,GALLON};



int main(){
	Jar_Type milk_jug = QUART;
	cout << milk_jug << endl;
	Jar_Type milk_jug2 = CUP;
	cout << milk_jug2 << endl;

	if(milk_jug2 == milk_jug){
		cout << "ok"  << endl;
	}

	system("pause");

	return 0;
}