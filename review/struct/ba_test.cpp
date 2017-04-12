#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
/************************************************************************/
/* 这里约定：占用即表示本身大小及其后的空余空间
/************************************************************************/
struct MyStruct1	// 起始地址能被8整除
{
	char a;			// 8
	double b;		// 8
	float c;		// 4
	int d;			// 4
} m1;				// 24

struct MyStruct2	// 起始地址能被8整除
{
	int a;			// 4
	float b;		// 4
	char c;			// 8 // 后面 double的起始地址要能被8 整除，所以c补齐8个字节
	double d;		// 8		
} m2;				// 24

struct MyStruct3	// 起始地址能被8整除
{
	short a;		// 2
	char b;			// 6 // 同理，后面的元素的起始地址要能被 8 整除，所以b只要占用6
	double c;		// 8
	int d;			// 8 // 需要在其后填充一些字节，以保证在分配数组之后，每个数组元素要满足起始地址约束
} m3;				// 24

struct MyStruct4
{
	char a;			// 2 // 能被4整除的地址 +2之后能被2整除，所以a只要补1个字节
	short b;		// 2 
	int c;			// 4
} m4;				// 8

struct MyStruct5	// 起始地址能被8整除
{
	double a;		// 8
	float b;		// 4
	int c;			// 4	
	short d;		// 2
	char e;			// 6 因为后面紧紧挨着的MyStruct5 变量（在分配数组的时候）起始地址也要能被8整除，所以这个结构体总的大小必须是8的整数倍
} m5;				// 24

struct MyStruct6	// 除4对齐
{
	short a;		// 2
	char b;			// 2
	long c;			// 4
	short d;		// 4  // 保证数组后面的元素也符合规则 （结构体首地址可以除4）
} m6;				// 12

struct MyStruct7	// 4 对齐
{
	int a;			// 4
	char b;			// 2
	short c;		// 2
	char d[6];		// 8
} m7;					// 16

int main(){
	printf("m1 size : %d\n",sizeof m1);
	printf("m2 size : %d\n",sizeof m2);
	printf("m3 size : %d\n",sizeof m3);
	printf("m4 size : %d\n",sizeof m4);
	printf("m5 size : %d\n",sizeof m5);
	printf("m6 size : %d\n",sizeof m6);
	printf("m7 size : %d\n",sizeof m7);

	// offsetof 计算成员离结构体首地址偏移的字节数
	printf("MyStruct1 b offset : %d\n",offsetof(struct MyStruct1,b));	// b偏移8个字节，所以成员a占用8个字节
	printf("MyStruct2 d offset : %d\n",offsetof(struct MyStruct2,d));	// d偏移了16个字节 
	printf("MyStruct3 c offset : %d\n",offsetof(struct MyStruct3,c));	// 偏移8
	printf("MyStruct4 b offset : %d\n",offsetof(struct MyStruct4,b));	// 偏移2
	printf("MyStruct5 e offset : %d\n",offsetof(struct MyStruct5,e));	// 偏移16
	printf("MyStruct6 c offset : %d\n",offsetof(struct MyStruct6,c));	// 偏移4
	printf("MyStruct7 c offset : %d\n",offsetof(struct MyStruct7,c));	// 偏移
	system("pause");
	return 0;
}