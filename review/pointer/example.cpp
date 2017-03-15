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

// 直接用二级指针遍历二级数组
// strings指向一个指针数组，这个函数执行完之后，指针数组中元素的值，
// 要么指向了字符串尾部'\0'的地址值，要么指向value这个字符，要么没有变，指向字符串的头部
// main函数中最后的for 循环证明了这一点
static int find_char2(char ** strings,int value){
	while( * strings != NULL){
		while( ** strings){   // ** strings 等价于  * strings[i]
			// 列偏移1  (* strings ) ++  加到 strngs[i]这个指针变量上去了。多次搜索就会出错 。
			if(* ((* strings ) ++) == value){
				return 1;
			}
		}
		// 行偏移1
		strings ++; // strings ++ 等价于 strings = &strings[i];
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