#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[]){
	int ch = fgetc(stdin);
	fputc(ch,stdout);
	char buf[255];
	
	char * str = fgets(buf,255,stdin);
	fputs(str,stdout);
	system("pause");
	return EXIT_SUCCESS;
}