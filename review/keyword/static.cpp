#include "helpers.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

// ʹ���ⲿ�ļ���external���͵ı�����ȫ�ֱ�����
extern int mainApp;
// ���д��벢����������󣬵������������ʹ�����������
// ��Ϊ����ļ�����һ���ļ���ʵ������Ϊinternal���ͣ�����ʹ�ûᱨ��
extern int cppApp;

int main(){
	int a = 10;
	int b = 11;
	swap(&a,&b);
	cout << a << " " << b << endl; 

	// �޷�����
	// inner_func();

	cout << mainApp << endl;

	//  error LNK2001: �޷��������ⲿ���� "int cppApp" (?cppApp@@3HA)
	// cout << cppApp << endl;

	system("pause");
	return 0;
}