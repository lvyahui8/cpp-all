#include <stdio.h>
#include <stdlib.h>


int main(){
	short shortVar = 10;
	int intVar = 80;
	short * p1 = & shortVar;
	int * p2 = & intVar;
	// printf("%d\n",* p1);	// 10
	// printf("%d\n",* p2);	// 80
	// *p1 = 1;
	// *p2 = 8;
	// printf("%d\n",* p1);	// 1
	// printf("%d\n",* p2);	// 8
	// system("pause");
	int *  * p2p = & p2;
	(char *) * p2p = & p2;
	// printf("%d\n",**p2p);	// 80
	// printf("%d\n",sizeof(p2p));
	printf("%x\n",p2);
	printf("%x\n",(char*) p2);

	// int a = 0x12345678;
	// return *(char*)(&a) == (char) a;
	int a = 0x12345678;
	int * pa = &a ;
	char * pch = (char *) pa;
	char ch = (char) a;
	printf("%x\n",*pch);
	printf("%x\n",ch);
	system("pause");
	return 0;
}
