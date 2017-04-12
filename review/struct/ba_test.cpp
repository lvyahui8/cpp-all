#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
/************************************************************************/
/* ����Լ����ռ�ü���ʾ�����С�����Ŀ���ռ�
/************************************************************************/
struct MyStruct1	// ��ʼ��ַ�ܱ�8����
{
	char a;			// 8
	double b;		// 8
	float c;		// 4
	int d;			// 4
} m1;				// 24

struct MyStruct2	// ��ʼ��ַ�ܱ�8����
{
	int a;			// 4
	float b;		// 4
	char c;			// 8 // ���� double����ʼ��ַҪ�ܱ�8 ����������c����8���ֽ�
	double d;		// 8		
} m2;				// 24

struct MyStruct3	// ��ʼ��ַ�ܱ�8����
{
	short a;		// 2
	char b;			// 6 // ͬ�������Ԫ�ص���ʼ��ַҪ�ܱ� 8 ����������bֻҪռ��6
	double c;		// 8
	int d;			// 8 // ��Ҫ��������һЩ�ֽڣ��Ա�֤�ڷ�������֮��ÿ������Ԫ��Ҫ������ʼ��ַԼ��
} m3;				// 24

struct MyStruct4
{
	char a;			// 2 // �ܱ�4�����ĵ�ַ +2֮���ܱ�2����������aֻҪ��1���ֽ�
	short b;		// 2 
	int c;			// 4
} m4;				// 8

struct MyStruct5	// ��ʼ��ַ�ܱ�8����
{
	double a;		// 8
	float b;		// 4
	int c;			// 4	
	short d;		// 2
	char e;			// 6 ��Ϊ����������ŵ�MyStruct5 �������ڷ��������ʱ����ʼ��ַҲҪ�ܱ�8��������������ṹ���ܵĴ�С������8��������
} m5;				// 24

struct MyStruct6	// ��4����
{
	short a;		// 2
	char b;			// 2
	long c;			// 4
	short d;		// 4  // ��֤��������Ԫ��Ҳ���Ϲ��� ���ṹ���׵�ַ���Գ�4��
} m6;				// 12

struct MyStruct7	// 4 ����
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

	// offsetof �����Ա��ṹ���׵�ַƫ�Ƶ��ֽ���
	printf("MyStruct1 b offset : %d\n",offsetof(struct MyStruct1,b));	// bƫ��8���ֽڣ����Գ�Աaռ��8���ֽ�
	printf("MyStruct2 d offset : %d\n",offsetof(struct MyStruct2,d));	// dƫ����16���ֽ� 
	printf("MyStruct3 c offset : %d\n",offsetof(struct MyStruct3,c));	// ƫ��8
	printf("MyStruct4 b offset : %d\n",offsetof(struct MyStruct4,b));	// ƫ��2
	printf("MyStruct5 e offset : %d\n",offsetof(struct MyStruct5,e));	// ƫ��16
	printf("MyStruct6 c offset : %d\n",offsetof(struct MyStruct6,c));	// ƫ��4
	printf("MyStruct7 c offset : %d\n",offsetof(struct MyStruct7,c));	// ƫ��
	system("pause");
	return 0;
}