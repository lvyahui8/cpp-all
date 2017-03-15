#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

int main(){
	for (int i = 1; i <= 4 ; i ++)
	{
		// switch具有穿透性，这在其余语言中也是如此
		switch ( i % 2 )
		{
		case 0:
			printf("even\n");
		case 1:
			printf("odd\n");
		}
	}
	system("pause");
	return 0;
}