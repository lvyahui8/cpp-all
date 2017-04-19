#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[]){
	
	printf("%s\n","sam" + 1);	// 字符串实际是指针常量值，+1将指向下一个字符，与先声明一个指针常量再+1没区别
	printf("%c\n",*"sam");
	printf("%c\n","sam"[1]);
	printf("%s\n",& "sam"[1]);
	
	system("pause");
	return EXIT_SUCCESS;
}