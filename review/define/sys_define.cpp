#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[]){
	
	printf("%s\n",__FILE__);
	printf("%d\n",__LINE__);
	printf("%s\n",__DATE__);	// �����������
	printf("%s\n",__TIME__);	// �������ʱ��
	// printf("%s\n",__STDC__); �����������ѭANSI C ��ֵ����1������δ����
	system("pause");
	return EXIT_SUCCESS;
}