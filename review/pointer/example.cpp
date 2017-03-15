#include <iostream>
#include <cstdlib>

using namespace std;

static size_t strlen (char * str){
	int len = 0;
	while( * str++ ) len ++;
	return len;
}

static int find_char(char ** strings,char value){
	char * str;
	
	while((str = * strings++ ) != NULL){
		while(*str){
			if( * str++ == value){
				return 1;
			}
		}
	}

	return 0;
}

// ֱ���ö���ָ�������������
// stringsָ��һ��ָ�����飬�������ִ����֮��ָ��������Ԫ�ص�ֵ��
// Ҫôָ�����ַ���β��'\0'�ĵ�ֵַ��Ҫôָ��value����ַ���Ҫôû�б䣬ָ���ַ�����ͷ��
// main����������for ѭ��֤������һ��
static int find_char2(char ** strings,int value){
	while( * strings != NULL){
		while( ** strings){   // ** strings �ȼ���  * strings[i]
			// ��ƫ��1  (* strings ) ++  �ӵ� strngs[i]���ָ�������ȥ�ˡ���������ͻ���� ��
			if(* ((* strings ) ++) == value){
				return 1;
			}
		}
		// ��ƫ��1
		strings ++; // strings ++ �ȼ��� strings = &strings[i];
	}

	return 0;
}


int main (){
	// cout << strlen("hello world") << endl;	// 11
	char strings[4][10] = {"hello","world","lv","yahui"};

	int n = 4;
	char ** strs = new char*[n];
	for (int i = 0 ; i < n; i ++)
	{
		strs[i] = strings[i];
	}
	// cout << find_char(strs,'w') << endl;
	cout << find_char2(strs,'w') << endl;
	
	for (int i = 0 ; i < n; i++)
	{
		cout << strs[i] << endl;
	}

	delete strs;

	system("pause");
	return 0;
}