/************************************************************************/
// �߽���� 
// ��ҪҪ���������ĵ�
// 1���ṹ�����ʼλ�ã������ǽṹ�жԱ߽�Ҫ�����ϸ������������Ҫ���λ�ã�
//		����double���͵���ʼ��ַԼ��Ϊ8 ���ڻ����������������ˣ�
//		�����һ���ṹ�����double���ͣ���ṹ�屾������ʼ��ַҪ�ܱ�8����
// 2����ʼ��ַԼ���ͱ����Ĵ�С ��windows�£�����ʹ��__alignof(type)���鿴type���ͣ��������ͣ�����ʼ��ַԼ��
// 3�������ԱҲ��struct union֮������ͣ�������Ҫ�չ˵����֣�����Ҫ�����Ա�ܷ�����ʼ��ַԼ��
// 4��һ��������ͣ�������Ҫ��������һЩ�ֽڣ��Ա�֤�ڷ�������֮��ÿ������Ԫ��Ҫ������ʼ��ַԼ��
// �жϷ���
// ����һ��ǰ�浥Ԫ�Ĵ�С�����Ǻ��浥Ԫ��С����������������ǾͲ���;
// ������֮����һ��Ԫ�ص���ʼ��ַҪ�ܱ�����ʼ��ַԼ����������ǰԪ��Ҫ��������뵽��һ��Ԫ�ص���ʼ��ַ,
// ��һ����ʼ��ַԼ��ǡ�����䱾���Ĵ�С����������Ĺ������ã�

// ������������ṹ��Ĵ�С����������ֽڵ�������

/************************************************************************/
#include <stdio.h>
#include <stdlib.h>

struct align1
{
	char a;
	int b;
	char c;
} sim1,sim2;

// --sim1------ ----sim2----
// a---bbbbc--- a---bbbbc---
// ����Ľṹ������У�sim1����ʼ��ַ�����ܱ�4����
// ��Աa����ʼ��ַҲ��sim1����ʼ��ַ��aռ��һ���ֽ�
// ��Աb����ʼ��ַҲ�����ܱ�4����������Ҫ������Աa��
// ����Ҫ��a֮������3���ֽڿ�ʼ���b����ôaʵ��ռ����4�ֽ�
// ��Ϊ��Աb�Ĵ�СΪ4���ֽڣ����Գ�Աc�Ŀ��Խ�����b�ţ�
// �����ı���Ҳ������룬����cʵ��ҲҪռ��4���ֽ�
// ��������sim1ռ��12 �ֽ�

// ���õĳ�Ա����˳������Ż��ռ�

struct align2
{
	int b;
	char a;
	char c;
} sim3,sim4;

int main(){
	printf("%d\n",sizeof sim1);
	printf("%d\n",sizeof sim3);
	system("pause");
	return 0;
}



