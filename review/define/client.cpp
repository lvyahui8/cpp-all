#include <stdio.h>
#include <stdlib.h>

// ��������뵽�����ַ�����
// ���� �ں궨���У��ڽ��ַ����Զ����ӵ�����ʹ���Ǻ����װ�һ���ַ����ֳɼ���
#define PRINT(FORMAT,VALUE) \
	printf("The value is " FORMAT "\n",VALUE)

// #argument ���͵Ľṹ�������ת��Ϊһ���ַ���
#define PRINT2(FORMAT,VALUE) \
	printf("The value of " #VALUE \
		" is " FORMAT "\n",VALUE);
// ## �������ߵķ�������Ϊһ�����ţ���Ϊ��;֮һ��������ӷ�����ı�Ƭ�δ�����ʶ��
// �����ǣ�����֮��ı�ʶ�������ǺϷ��ģ��Ѿ�������ı�������
#define ADD_TO_SUM(sum_number,value) \
	sum ## sum_number += value

int main(){
	PRINT("%d",1); // The value is 1
	PRINT2("%d",1 + 2); // The value of 1 + 2 is 3
	int sum1 = 2;
	ADD_TO_SUM(1,25);			// ����sum1 += 25
	printf("%d\n",sum1);
	system("pause");
	return 0;
}