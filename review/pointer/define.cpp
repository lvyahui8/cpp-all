#include <iostream>
#include <cstdlib>

using namespace std;
int main (){
	int a = 10;
	int *b = &a;
	// 下面两者是等价的，*解引用符具有自右向左的结合性
	int *(*c) = &b;				
	int **d  = &b;

	cout << * b ++ << endl;		// 10 与 * (b++)等价 ，执行完b已经偏向a之后的一个整型变量区域M
	cout << ** c ++ << endl;	// 未知，与 ** (c++)等价，c++的值依然是b的地址，** 就是访问未知变量区域M
	cout << c - d << endl;		// 1，差一个整型变量占用的大小
	system("pause");
	return 0;
}