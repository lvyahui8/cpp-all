#include <iostream>
using namespace std;

int main(){
	// ��������ָ�볣������һλ�����У�������ָ���һ��Ԫ�صĵ�ַ��
	// �ڶ�ά�����У���������ָ���һ�е��׵�ַ������˵ָ���һ�����飬����ֵ��Ȼ�ǵ�һ��Ԫ�صĵ�ַ��

	// ���鲢����ȫ�ȼ���ָ�룬��������һЩ��ָ����ȫ��ͬ��������
	// ֻ�е�����ing�ڱ���ʽ��ʹ��ʱ���������Ż�Ϊ������һ��ָ�볣��
	int arr [4];

	// ����������£�������������ָ�볣����ʾ
	// 1������sizeof�Ĳ���������ʱsizeof������������ĳ��ȣ������� ָ�������ָ�� �Ĵ�С
	cout << sizeof arr << endl; // sizeof �ǹؼ��ֲ��Ǻ���
	// 2��& ȡ��ַ�Ĳ���������ʱ�õ�����һ��ָ�������ָ�룬������һ��ָ����ֵ��ָ��
	cout << & arr << endl;
	// �±겻���ָ������죬����ָ��������ܱ��±�죬��Ҫ��ָ��������±����㶼�г˷�������p + 1 �������Եĳ˷��ģ�
	return 0;
}