#include <cstdio>
#include <cstring>
#include <ctime>


bool is_start_with(const char * str1, const char * str2){
	while((*str2 != '\0') && * str1 ++ == * str2 ++ );

	return * str2 == '\0';
}

bool is_end_with(const char * str1, const char * str2){
	size_t len1 = strlen(str1);
	size_t len2 = strlen(str2);
	const char * pCh1 =  str1 + len1;
	const char * pCh2 = str2 + len2;
	while(pCh2 != str2 && * pCh1-- == * pCh2--);

	return pCh2 == str2;
}

void ltrim(const char * str, const char * chars){
	size_t chars_len = strlen(chars);
	const char * pCh = str;
	for(; * pCh != '\0'; ){
		if (is_start_with(pCh,chars)){
			pCh += chars_len;
		} else{
			break;
		}
	}
}

int main(){
	int n = 10000000;
	int t = clock();
	for ( int i = 0 ; i < n; i ++ ){
		ltrim("lvyahui","lv");
	}
	printf("c method cost time :%d ms\n", clock() - t );
	getchar();
	return 0;
}