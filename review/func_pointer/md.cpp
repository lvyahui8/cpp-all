#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define OPTION_P        (1<<0)  
#define OPTION_D        (1<<1)  
#define OPTION_H        (1<<2)  

const char * command_name = "md";

extern char *optarg;  
extern int optind;  
extern int opterr;  
extern int optopt;  
extern int getopt(int argc, char * const argv[], const char *optstring);

static void usage(void){
	fprintf(stderr,
		"Usage: %s [OPTIONS]\n"
		"\t[-p path]\n"
		"\t[-d dir]\n"
		,command_name);
	exit(1);
}
static int PRS(int argc, char **argv, int *opts)  
{  
    int retval, prog_num;  
    char ch;  
  
    *opts &= 0x00000000;  
 
    while ((ch = getopt(argc, argv, "pdh")) != -1) {  
        switch (ch) {  
            case 'p':  
                *opts |= OPTION_P;  
                break;  
            case 'd':  
                *opts |= OPTION_D;  
                printf("-d dir=%s\n", optarg);  
                break;  
            case 'h':  
                *opts |= OPTION_H;  
                usage();  
                break;  
            default:  
				// fprintf(stderr,   
				//         "our: %s: invalid option -- '%c'\n",  
				//         command_name, optopt);  
				usage();
                exit(1);  
                break;  
        }  
    }  
  
    return 0;  
}  

int main(int argc,char * argv[]){
	int opts;  
	int retval;
	retval = PRS(argc, argv, &opts);  
	if (retval < 0) {  
		exit(1);  
	}  
	printf("ok\n"); 
	return 0;
}