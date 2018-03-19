#include <cstdio>
#include <cstring>
#include <ctime>
#include <iostream>

using namespace std;

int main(){
	int * p;		// 指针,常用来操作一维数组，可以看做列指针	
	int * parr[4];		// 指针数组
	int (*pa)[4];		// 指向元素个数为4的整形数组的指针（即指向数组的指针）,可以看做二维数组名，可以看做行指针
	int ** pp;		// 二级指针
	int * f();		// 这只是一个函数声明，并没有创建变量，如果写 int * f() = NULL;将出错
	int (*ff)();		// 函数指针，指向一个无参、返回值为整数的函数
	int *(*ffxx)();		// 函数指针，指向一个无参、返回值为整数指针的函数
	int (*fa[4])();		// 函数指针数组，每一个数组元素都是一个函数指针：
				// 指向一个无参、返回值为整数的函数
	int *(*fax[4])();	// 函数指针数组，每一个数组元素都是一个函数指针：
				// 指向一个无参、返回值为整型指针的函数
	int **(*fab[4])();	// 函数指针数组，每一个数组元素都是一个函数指针：
				// 指向一个无参、返回值为二级整型指针的函数
	int (* update(int,int (*l(int))))(int);	// 这一句也是一个函数声明，而不是变量声明
	
	// 函数有两个参数：整数、函数指针，返回值为一个函数指针
	// 仔细看可以看到，返回值表示的函数与第二个参数表示的函数，形参和返回值是完全一样的
	// 这种方法经常出现在一些程序里：添加新的回调函数、并返回旧的回调函数!!!!!
	int (* (*update2)(int,int * (*l)(int)))(int) = NULL;
	const int * pc;		// 常量指针，指向的变量不可变
	int * const cp = 0;	// 指针常量，指针本身不能变
	const int * pcc[4];	// 常量指针数组，每个成员都是一个常量指针
	int * const cpp[4] = {0,0,0,0};	// 指针常量数组，每一个元素都是一个不可变的指针


	return 0;
}
