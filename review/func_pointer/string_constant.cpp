#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[]){
	
	printf("%s\n","sam" + 1);	// �ַ���ʵ����ָ�볣��ֵ��+1��ָ����һ���ַ�����������һ��ָ�볣����+1û����
	printf("%c\n",*"sam");
	printf("%c\n","sam"[1]);
	printf("%s\n",& "sam"[1]);
	
	system("pause");
	return EXIT_SUCCESS;
}