#include <stdio.h>
#include <stdlib.h>
/************************************************************************/
/* λ�ε���������ͨ�ṹ�����ƣ��������Ա�Ǳ�ʾһ������λ��
/* �����ֶΣ������ṹ�壩ʵ�ʴ洢��һ���������ͱ����Ŀռ���
/* λ�ε��ŵ����ṩ���򵥿��ٵķ������ʻ��޸��ض�λ����ͬ�Ĺ��ܽ���λ����Ҳ��ʵ�֡�λ�ε�ȱ������ֲ�Բ�
/************************************************************************/
// ��������������ҵ������λ��
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
} m_reg;	// �պô���һ��32 λ��4�ֽڣ�������

// λ��ֻ����  int ��signed int ������unsigned int��������ƻ�λ�ε����������һ����ͨ�Ľṹ��
struct SIMPLE // 4
{
	unsigned char a : 1;		// 2 
	unsigned short b : 1;		// 2
	unsigned int c	: 1;		// 4
} simple;

// λ�β��ܸ���ͨ��Ա���ʹ�ã�����ʧЧ
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