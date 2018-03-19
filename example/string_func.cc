#include <cstdio>
#include <cstring>
#include <ctime>

void strlcpy(char * dest,const char * src , int maxlength){
	while(--maxlength > 0 && (*dest++ = *src++));

	if(maxlength <= 0) {
		* dest = '\0';
	}
}

int main(){
	char str1[5] = "1234";
	char str2[9] = "87654321";
	strlcpy(str1,str2,sizeof(str1));
	strlcpy(str2,"12",sizeof(str2));
	puts(str1);
	puts(str2);
	return 0;
}
