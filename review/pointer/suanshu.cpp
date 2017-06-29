#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
	// int * p1 = (int *) 0x100;
	// int * p2 = (int *) 0x10c;
	// printf("p2-p1 : %d\n",p1 - p2);
	// int arr[5] ;
	// printf("%d\n",&arr[4] - &arr[0] == 4 - 0); // 1
	// const int readOnlyVar = 10;
	// int * pROVar = (int *) & readOnlyVar;
	// * pROVar = 11;
	// printf("%d\n",readOnlyVar);
	// printf("%c\n",* "hello");		//	h
	// printf("%s\n", "hello" + 1);	//	ello

	//char * str = "hello";
	// char * const strBuff = (char * ) malloc (6);
	// strcpy(strBuff,"hello");
	// char * str = strBuff;
	// free(strBuff);
	int const * p1 ;
	const int * p2 ;
	int * const p3 = NULL;
	const int * const p4 = NULL;
	system("pause");
	return 0;
}