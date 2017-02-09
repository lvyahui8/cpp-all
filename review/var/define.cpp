/*
* static 关键字
* 
* 当它作用于函数时，或用于代码块之外（函数体外部）的变量声明时，static关键字
* 用于修改标识符的链接属性，从external改为internal，但标识符的存储类型和作用
* 域不受影响。用这种方式声明的函数或者变量只能在声明它们的源文件中访问。
* 
* 当它作用于代码块内部个变量声明时，static关键字用于修改变量的存储类型，从自动
* 变量修改为静态变量，但是变量的链接属性和作用域不受影响。用这种方式声明的变量
* 在程序执行之前创建，并在程序的整个执行期间一直存在，而不是每次在代码块开始执
* 行时创建，在代码块执行完毕后销毁。
*/
int	a = 5;
extern int b;
static int c;

int d(int e){
	int f = 15;
	register int b;
	static int g = 20;
	extern int a;
	{
		int e;
		int a;
		extern int h;
	}
	{
		int x;
		int e;
	}
	return 0;
}

static int i(){
	return 1;
}