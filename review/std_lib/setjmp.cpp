#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

jmp_buf restart;

void exp_func(){
	for(static int i = 1 ;i < 3;){
		longjmp(restart,i++);
	}
}

int main(){
	int value ;
	switch(value = setjmp(restart)){
	default :
		fputs("Fatal error:Divide by 0!\n",stderr);
		break;
	case 1:
		fputs("Negligible exception!\n",stderr);
	case 0:
		exp_func();
		puts("Invoke success!");
	}
	system("pause");
	return 0;
}