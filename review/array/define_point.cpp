#include <stdio.h>

int main(){
	int matrix[3][10] = {{1,2,3,4,5}};
	int (*p)[10] = matrix;
	
	for (int i = 0 ;i < 10; i++)
	{
		printf("%d ",*(*p + i));
	}
	// 在C中，此语句是合法的，但是却是有问题的，vp在进行算数运算时，
	// 它的值根据空数组的长度进行调整 也就是 0，有的编译器可以捕获这种错误
	// int (*vp) [] = matrix;

	// 下面两者等价，都是将第一行的首地址赋值给一级指针，此指针+1，将在行内偏移1个整型元素
	int * pi1 = &matrix[0][0];
	int * pi2 = matrix[0];

	getchar();

	return 0;
}