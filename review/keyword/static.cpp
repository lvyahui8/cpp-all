#include "helpers.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

// 使用外部文件中external类型的变量（全局变量）
extern int mainApp;
// 此行代码并不会引起错误，但是如果后面有使用这个变量，
// 因为这个文件在另一个文件中实际声明为internal类型，所以使用会报错
extern int cppApp;

int main(){
	int a = 10;
	int b = 11;
	swap(&a,&b);
	cout << a << " " << b << endl; 

	// 无法调用
	// inner_func();

	cout << mainApp << endl;

	//  error LNK2001: 无法解析的外部符号 "int cppApp" (?cppApp@@3HA)
	// cout << cppApp << endl;

	system("pause");
	return 0;
}