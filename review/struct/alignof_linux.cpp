#include <stdio.h>
#include <stdlib.h>

int main(){
	printf("char: %d\n",__alignof__(char));
	printf("short: %d\n",__alignof__(short));
	printf("int: %d\n",__alignof__(int));
	printf("long: %d\n",__alignof__(long));
	printf("double: %d\n",__alignof__(double));
	//system("pause");
	return 0;
}