/************************************************************************/
/* fgetc 和 fputc才是真正的函数
/* getc  putc  getchar putchar  是定义在stdio.h中的宏
/* 但其实现在C版本基本已经用函数实现这些宏，
/* 可以用（func）() 函数指针的方式调用到函数 ,
如 getchar()是调用的宏
但是 (getchar)()调用的是函数版本

C语言中，允许函数与宏同名，此称为宏覆盖
这并不存在标识符冲突，因为在预编译阶段，使用宏名的地方都被宏值替换掉了
但要求，同名的宏必须写在同名函数之后
同名策略可参考博客
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
	println("hello");	// 因为宏实现中使用了自动相邻字符串连接，所以传参只能是字符串字面常量  而不能是 println(str);
	(println)(str);
	system("pause");
	return 0;
}