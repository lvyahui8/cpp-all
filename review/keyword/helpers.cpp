#include "helpers.h"
#include <iostream>
using namespace std;

/************************************************************************/
/* ��static�����ں�������ʱ���������ڴ����֮��ı�������ʱ��static�ؼ���
/* �����޸ı�ʶ�����������ԣ���external��Ϊ��internal���ͣ����Ǳ�ʶ���Ĵ�
/* �����ͺ���������Ӱ�졣�����ַ�ʽ�����ĺ����ͱ���ֻ�����������ǵ�Դ��
/* ���з���
/************************************************************************/

int mainApp = 0x99;
static int cppApp = 1;

// ��static�ؼ��ֱ��޸�ûinternal����
static void inner_func(){
	cout << "inner func" << endl;
}

// public function
// ����Ĭ����extern���ͣ��ⲿ���Է���
extern void swap(int * a, int * b){
	*a = *a + *b;
	*b = *a - *b;
	*a = *a - *b;
}