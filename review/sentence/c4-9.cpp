#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

int main(){
	for (int i = 1; i <= 4 ; i ++)
	{
		// switch���д�͸�ԣ���������������Ҳ�����
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