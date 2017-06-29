#include <stdio.h>
#include <stdlib.h>


int main(){
	int arr [5];
	int a  = 10;
	int * const p = &a;
	//const int * p = &a;
	int * const pArr[5] = {0,&arr[1]};
	int i ; 
	for (i = 0 ; i < 5 ;i ++)
	{
		printf("%x\n",pArr[i]);
	}

	char * const options[5] = {
		"--list",
		"--prefix",
		"--with"
	};

	for (i = 0 ; i < 5 ;i ++)
	{
		if (NULL != options[i]){
			printf("%s\n",options[i]);
		}
	}

	char * tmpStr = "hello";
	// options[0] = tmpStr; // 修改指针指向新的字符串常量
	// *(options[0]) = '+'; // 修改第一个元素指向区域的内容
	// * (options[0] + 1) = '+';
	// char * str = "hello";
	// *(str + 3) = 'w';
	// printf("%s\n",str);
	system("pause");
	return 0;
}