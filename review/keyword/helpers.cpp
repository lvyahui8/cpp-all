#include "helpers.h"
#include <iostream>
using namespace std;

/************************************************************************/
/* 当static作用于函数定义时，或者用于代码块之外的变量声明时，static关键字
/* 用于修改标识符的链接属性，从external改为了internal类型，但是标识符的存
/* 储类型和作用域不受影响。用这种方式声明的函数和变量只能在声明它们的源文
/* 件中访问
/************************************************************************/

int mainApp = 0x99;
static int cppApp = 1;

// 因static关键字被修改没internal类型
static void inner_func(){
	cout << "inner func" << endl;
}

// public function
// 方法默认是extern类型，外部可以访问
extern void swap(int * a, int * b){
	*a = *a + *b;
	*b = *a - *b;
	*a = *a - *b;
}