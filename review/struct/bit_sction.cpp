#include <stdio.h>
#include <stdlib.h>
/************************************************************************/
/* 位段的声明和普通结构体类似，不过其成员是表示一个或多个位，
/* 所有字段（整个结构体）实际存储在一个或多个整型变量的空间中
/* 位段的优点是提供更简单快速的方法访问或修改特定位，相同的功能借助位操作也能实现。位段的缺点是移植性差
/************************************************************************/
// 假设这个机器从右到左分配位段
struct DISK_REGISTER_FORMAT {
	unsigned	command			:	5;
	unsigned	sector			:	5;
	unsigned	track			:	9;
	unsigned	error_code		:	8;
	unsigned	head_loaded		:	1;
	unsigned	write_protect	:	1;
	unsigned	disk_spinning	:	1;
	unsigned	error_occurred	:	1;
	unsigned	ready			:	1;
} m_reg;	// 刚好存在一个32 位（4字节）整型中

// 位段只允许  int 、signed int 、或者unsigned int，否则会破坏位段的声明，变成一个普通的结构体
struct SIMPLE // 4
{
	unsigned char a : 1;		// 2 
	unsigned short b : 1;		// 2
	unsigned int c	: 1;		// 4
} simple;

// 位段不能跟普通成员混合使用，否则失效
struct SIM2 {
	char a ;
	int b ;
	unsigned c : 10;
} sim2;

int main(){
	printf("sizeof m_reg : %d\n",sizeof m_reg);
	printf("sizeof simple : %d\n",sizeof simple);
	printf("sizeof sim2 : %d\n",sizeof sim2);
	system("pause");
	return 0;
}