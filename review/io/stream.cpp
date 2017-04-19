#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[]){
	FILE * fp = fopen("stream_file.data","w+");
	if(fp == NULL){
		perror("no such file!");
		exit(EXIT_FAILURE);
	}
	
	if(fp != NULL){
		fclose(fp);
	}
	system("pause");
	return EXIT_SUCCESS;
}