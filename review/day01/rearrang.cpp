#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#define	MAX_COLS	20		//	所能处理的最大序列号
#define	MAX_INPUT	1000	//	每个输入行的最大长度

using namespace std;

int read_column_numbers(int columns[] , int max);
void rearrange(char * output,char const * input , int n_columns, int const columns[]);

int main(){
	int n_columns;
	int columns[MAX_COLS];
	char input[MAX_INPUT];
	char output[MAX_INPUT];
	
	// 读取该串列标号
	n_columns = read_column_numbers(columns,MAX_COLS);
	// 读取、处理和打印剩余的输入行
	while(gets(input) != NULL ){
		cout << "Original input : " << * input << endl;
		rearrange(output,input,n_columns,columns);
		cout << "Rearranged line: " << output << endl;
	}
	system("pause");
	return 0;
}

// 读取列标号，如果超出规定访问则不予理会
int read_column_numbers(int columns[],int max){
	int num = 0;
	int ch ;
	// 取得列标号，如果所读取的书小于0则停止
	while (num < max && scanf("%d" ,&columns[num]) == 1 && columns[num] >= 0)
	{
		num ++;
	}

	// 确认已经读取的标号为偶数个，因为他们是以对的形式出现的
	if(num % 2 != 0){
		puts("Last column number is paired: ");
		exit(-1);
	}

	while ((ch = getchar()) != EOF && ch != '\n')
	{
	}
	return num;

}

// 处理输入行，将指定列的字符连接在一起，输出行以NULL结尾
void rearrange(char * output,char const * input , int n_columns, int const columns[]){
	int col;		// columns数组的下标
	int output_col;	// 输出列计数器
	int len;		// 输入行的长度

	len = strlen(input);
	output_col = 0;

	// 处理每一对列标号
	for (col = 0; col < n_columns; col += 2)
	{
		int nchars = columns[col + 1] - columns[col] + 1; 
		// 如果输入行结束或者数组已满，就结束任务
		if (columns[col] >= len || output_col == MAX_INPUT - 1)
		{
			break;
		}

		// 如果输入行数据空间不够，只复制可以容纳的数据
		if (output_col + nchars > MAX_INPUT - 1)
		{
			nchars = MAX_INPUT - output_col - 1;
		}

		// 复制数据
		strncpy(output_col + output, input + columns[col],nchars);
		output_col += nchars;
	}

	output[output_col] = '\0';
}