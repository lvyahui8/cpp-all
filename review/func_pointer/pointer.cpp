#include <stdio.h>
#include <stdlib.h>

int * funcation1(int a){
	printf("hello\n");
	return NULL;
}

int main(){

	// 定义一个指向函数的指针，函数返回值类型为整型指针
	int * (* fun1)(int) = & funcation1;
	// 在 c11的标准中，必须明确指定参数类型，即便在旧版本中，也提倡写清楚形参列表
	// error C2440: “初始化”: 无法从“int *(__cdecl *)(int)”转换为“int *(__cdecl *)(void)”
	// int * (* fun2)() = & funcation1;
	
	// &是可选的，因为函数名在使用时总是由编译器把它转换为函数指针，&只是显示的说明了编译器将要隐性执行的任务
	int * (* fun2)(int) = funcation1;

	// 定义了一个函数指针数组，每个元素是一个函数指针，指向函数类型返回值为整型指针
	int * (* funs[5])() ;

	// 1
	// 编译器首先将函数名转为指针，得到函数首地址，执行函数首地址开始的代码
	funcation1(0);

	// 2
	// 先解引用指针得到函数名，然后过程和1一样，多此一举
	(* fun1)(0);

	// 3
	// 直接通过指针调用，这是函数指针的常用方式
	fun1(0);

	system("pause");
	return 0;
}