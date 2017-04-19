#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[]){
	
	printf("%s\n",__FILE__);
	printf("%d\n",__LINE__);
	printf("%s\n",__DATE__);	// 被编译的日期
	printf("%s\n",__TIME__);	// 被编译的时间
	// printf("%s\n",__STDC__); 如果编译器遵循ANSI C 其值就是1，否则未定义
	system("pause");
	return EXIT_SUCCESS;
}