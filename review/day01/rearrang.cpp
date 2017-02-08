#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#define	MAX_COLS	20		//	���ܴ����������к�
#define	MAX_INPUT	1000	//	ÿ�������е���󳤶�

using namespace std;

int read_column_numbers(int columns[] , int max);
void rearrange(char * output,char const * input , int n_columns, int const columns[]);

int main(){
	int n_columns;
	int columns[MAX_COLS];
	char input[MAX_INPUT];
	char output[MAX_INPUT];
	
	// ��ȡ�ô��б��
	n_columns = read_column_numbers(columns,MAX_COLS);
	// ��ȡ������ʹ�ӡʣ���������
	while(gets(input) != NULL ){
		cout << "Original input : " << * input << endl;
		rearrange(output,input,n_columns,columns);
		cout << "Rearranged line: " << output << endl;
	}
	system("pause");
	return 0;
}

// ��ȡ�б�ţ���������涨�����������
int read_column_numbers(int columns[],int max){
	int num = 0;
	int ch ;
	// ȡ���б�ţ��������ȡ����С��0��ֹͣ
	while (num < max && scanf("%d" ,&columns[num]) == 1 && columns[num] >= 0)
	{
		num ++;
	}

	// ȷ���Ѿ���ȡ�ı��Ϊż��������Ϊ�������ԶԵ���ʽ���ֵ�
	if(num % 2 != 0){
		puts("Last column number is paired: ");
		exit(-1);
	}

	while ((ch = getchar()) != EOF && ch != '\n')
	{
	}
	return num;

}

// ���������У���ָ���е��ַ�������һ���������NULL��β
void rearrange(char * output,char const * input , int n_columns, int const columns[]){
	int col;		// columns������±�
	int output_col;	// ����м�����
	int len;		// �����еĳ���

	len = strlen(input);
	output_col = 0;

	// ����ÿһ���б��
	for (col = 0; col < n_columns; col += 2)
	{
		int nchars = columns[col + 1] - columns[col] + 1; 
		// ��������н������������������ͽ�������
		if (columns[col] >= len || output_col == MAX_INPUT - 1)
		{
			break;
		}

		// ������������ݿռ䲻����ֻ���ƿ������ɵ�����
		if (output_col + nchars > MAX_INPUT - 1)
		{
			nchars = MAX_INPUT - output_col - 1;
		}

		// ��������
		strncpy(output_col + output, input + columns[col],nchars);
		output_col += nchars;
	}

	output[output_col] = '\0';
}