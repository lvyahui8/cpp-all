#include <stdio.h>

int  main(int argc ,char * argv[]){
    if (argc > 0 ){
        for (int i = 0; * argv != NULL; ++i) {
            printf("argv[%d]: %s\n",i,* argv++);
        }
    }
    return 0;
}