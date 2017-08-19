#include <apue.h>
#include <string.h>
#include <sys/wait.h>

/*
 * 就像在命令行执行
 * cat /etc/services | /usr/bin/less
 */
int main(int argc, char * argv[]){
    int n;
    int fd[2];
    pid_t pid;
    char line[MAXLINE];
    FILE * fp;
    if((fp = fopen("/etc/services","r")) == NULL){
        err_sys("can't open file %s","/etc/services");
    }


    if ((pipe(fd) <0 )){
        err_sys("pipe error");
    }

    if((pid = fork()) < 0){
        err_sys("fork error");
    } else if ( pid > 0  )
    {
        close(fd[0]);
        while(fgets(line ,MAXLINE,fp) !=NULL){
            n = strlen(line);
            if(write(fd[1],line,n) != n){
                err_sys("write error to pipe");
            }
        }

        if(ferror(fp))
        {
            err_sys("write error to pipe");
        }
        close(fd[1]);

        if(waitpid(pid,NULL,0) < 0){
            err_sys("waitpid error");
        }
        exit(0);
    } else {
        close(fd[1]);
        // 以管道的输入作为此进程的输入
        if (fd[0] != STDIN_FILENO){
            if(dup2(fd[0],STDIN_FILENO) != STDIN_FILENO){
                err_sys("dup2 error");
            }
            close(fd[0]);
        }

        if(execl("/usr/bin/less","less",(char *) 0) < 0)
        {
            err_sys("execl error for %s","/usr/bin/less");
        }

    }
    return 0;
}
