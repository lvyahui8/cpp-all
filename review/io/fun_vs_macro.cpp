/************************************************************************/
/* fgetc �� fputc���������ĺ���
/* getc  putc  getchar putchar  �Ƕ�����stdio.h�еĺ�
/* ����ʵ����C�汾�����Ѿ��ú���ʵ����Щ�꣬
/* �����ã�func��() ����ָ��ķ�ʽ���õ����� ,
�� getchar()�ǵ��õĺ�
���� (getchar)()���õ��Ǻ����汾

C�����У����������ͬ�����˳�Ϊ�긲��
�Ⲣ�����ڱ�ʶ����ͻ����Ϊ��Ԥ����׶Σ�ʹ�ú����ĵط�������ֵ�滻����
��Ҫ��ͬ���ĺ����д��ͬ������֮��
ͬ�����Կɲο�����
http://www.cnblogs.com/menggucaoyuan/archive/2012/12/25/2832822.html
/************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



void println(char * s){
	printf("func:%s\n",s);
}

#define println(STR)	puts("macro:" STR "\n")

int main(){
	char * str = "hello";
	println("hello");	// ��Ϊ��ʵ����ʹ�����Զ������ַ������ӣ����Դ���ֻ�����ַ������泣��  �������� println(str);
	(println)(str);
	system("pause");
	return 0;
}