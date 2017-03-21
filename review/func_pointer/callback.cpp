#include <stdio.h>
#include <stdlib.h>

int serach(void * var1,void * var2,
	int (*cmp) (const void * const var1,const void * const var2)){
	if(cmp(var1,var2) == 0){
		return 1;
	}
	return 0;
}

int int_cmp(const void * const var1,const void * const var2){
	int * v1 = (int *) var1;
	int * v2 = (int *) var2;
	return * v1 - * v2;
}

int main(){
	int a = 10;
	int b = 10;
	printf("%d\n",serach(&a,&b,int_cmp));
	system("pause");
	return 0;
}