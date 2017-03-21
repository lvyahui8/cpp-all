#include <iostream>
#include <cstdlib>
using namespace std;

int main(){
	// 这两者并不等价，前者初始化一个字符数组元素，而后者创建一个字符串常量，并将指针指向该字符串常量
	// 下面代码显示了  msg1 指向的数组是可以修改的，而试图修改msg2指向的字符串常量会引起异常中断
	char msg1[] = "hello";
	char *msg2  = "hello";
	msg1[1] = 'w';
	* (msg2 + 1) = 'w';
	cout << msg1 << endl;
	cout << msg2 << endl;
	// 但是相反的 msg2 是一个指针变量，是可以被修改的，而msg1作为数组名，是不允许修改的
	msg2 = NULL;
	// msg1 = NULL;
	system("pause");
	return 0;
}