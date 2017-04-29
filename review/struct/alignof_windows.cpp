#include <stdio.h>
#include <stdlib.h>


int main(){
	printf("char: %d\n",__alignof(char));
	printf("short: %d\n",__alignof(short));
	printf("int: %d\n",__alignof(int));
	printf("_int64: %d\n",__alignof(__int64));
	printf("long: %d\n",__alignof(long));
	printf("double: %d\n",__alignof(double));
	system("pause");
	return 0;
}