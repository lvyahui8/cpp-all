#include <stdio.h>
#include <stdlib.h>

// 宏参数插入到常量字符串中
// 方法 在宏定义中，邻近字符串自动连接的特性使我们很容易把一个字符串分成几段
#define PRINT(FORMAT,VALUE) \
	printf("The value is " FORMAT "\n",VALUE)

// #argument 类型的结构将宏参数转换为一个字符串
#define PRINT2(FORMAT,VALUE) \
	printf("The value of " #VALUE \
		" is " FORMAT "\n",VALUE);
// ## 将其两边的符号连接为一个符号，作为用途之一，它允许从分离的文本片段创建标识符
// 问题是，连接之后的标识符必须是合法的（已经定义过的变量名）
#define ADD_TO_SUM(sum_number,value) \
	sum ## sum_number += value

int main(){
	PRINT("%d",1); // The value is 1
	PRINT2("%d",1 + 2); // The value of 1 + 2 is 3
	int sum1 = 2;
	ADD_TO_SUM(1,25);			// 变量sum1 += 25
	printf("%d\n",sum1);
	system("pause");
	return 0;
}