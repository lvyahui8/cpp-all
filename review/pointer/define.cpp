#include <iostream>
#include <cstdlib>

using namespace std;
int main (){
	int a = 10;
	int *b = &a;
	// ���������ǵȼ۵ģ�*�����÷�������������Ľ����
	int *(*c) = &b;				
	int **d  = &b;

	cout << * b ++ << endl;		// 10 �� * (b++)�ȼ� ��ִ����b�Ѿ�ƫ��a֮���һ�����ͱ�������M
	cout << ** c ++ << endl;	// δ֪���� ** (c++)�ȼۣ�c++��ֵ��Ȼ��b�ĵ�ַ��** ���Ƿ���δ֪��������M
	cout << c - d << endl;		// 1����һ�����ͱ���ռ�õĴ�С
	system("pause");
	return 0;
}