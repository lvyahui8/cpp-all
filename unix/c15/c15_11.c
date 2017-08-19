#include <apue.h>
#include <string.h>
#include <sys/wait.h>

/*
 * 就像在命令行执行
 * cat /etc/services | /usr/bin/less
 */
int main(int argc, char * argv[]){
    char line[MAXLINE];

    FILE * fpin, * fpout;
    if((fpin = fopen("/etc/services","r")) == NULL){
        err_sys("can't open file %s","/etc/services");
    }

    if((fpout = popen("/usr/bin/less","w")) == NULL){
        err_sys("popen error");
    }


        while(fgets(line ,MAXLINE,fpin) !=NULL){
            if (fputs(line ,fpout) == EOF){
                err_sys("fputs error to pipe");
            }
        }

        if(ferror(fpin))
        {
            err_sys("write error to pipe");
        }
        if(pclose(fpout) == -1){
            err_sys("pclose error");
        }
    return 0;
}
