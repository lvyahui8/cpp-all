#include <iostream>
#include <cstdlib>
using namespace std;

int main(){
	// �����߲����ȼۣ�ǰ�߳�ʼ��һ���ַ�����Ԫ�أ������ߴ���һ���ַ�������������ָ��ָ����ַ�������
	// ���������ʾ��  msg1 ָ��������ǿ����޸ĵģ�����ͼ�޸�msg2ָ����ַ��������������쳣�ж�
	char msg1[] = "hello";
	char *msg2  = "hello";
	msg1[1] = 'w';
	* (msg2 + 1) = 'w';
	cout << msg1 << endl;
	cout << msg2 << endl;
	// �����෴�� msg2 ��һ��ָ��������ǿ��Ա��޸ĵģ���msg1��Ϊ���������ǲ������޸ĵ�
	msg2 = NULL;
	// msg1 = NULL;
	system("pause");
	return 0;
}