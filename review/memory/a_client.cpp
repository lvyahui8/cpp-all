#include <stdio.h>
#include "alloc.h"
#include <stdlib.h>

int main(){
	int * arr = NULL;
	int n = 10;
	arr = MALLOC(n,int);
	for(int i = 0 ; i < n; i++){
		* (arr + i) = i;
	}
	printf("%d\n",arr[n-1]);
	free(arr);
	system("pause");
	return 0;
}