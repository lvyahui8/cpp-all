#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char * argv[]){
	int exit_status = EXIT_SUCCESS;
	FILE * input;
	
	while(* ++ argv != NULL ){
		input = fopen(* argv,"r");
		if(input == NULL){
			perror( * argv);
			exit_status = EXIT_FAILURE;
			continue;
		}
		
		FILE * output = fopen(strcat(* argv,".md5.data"),"w+");
		if(output != NULL){
			int ch;
			while ((ch = fgetc(input)) != EOF)
			{
				fputc(ch,output);
			}
			fclose(output);
		}
		

		if(input != NULL){
			fclose(input);
		}
	}
	
	system("pause");
	return EXIT_SUCCESS;
}