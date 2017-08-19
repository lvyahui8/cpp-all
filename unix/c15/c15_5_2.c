#include <apue.h>
#include <string.h>

/*
 *
 * [root@localhost c15]# ./c15_5.app
 * hello child
 * User defined signal 2
 * [root@localhost c15]# child done
 * 输出 user defined signal 2 的原因是 lib/tellwait.c:kill(pid, SIGUSR2);
 */
int main(int argc, char * argv[]){
    int n;
    int fd[2];
    pid_t pid;
    char line[MAXLINE];

    if ((pipe(fd) <0 )){
        err_sys("pipe error");
    }

    if((pid = fork()) < 0){
        err_sys("fork error");
    } else if ( pid > 0  )
    {
        char * msg = "hello child\n";
        write(fd[1],msg,strlen(msg));
        WAIT_CHILD();
        n = read(fd[0],line,MAXLINE);
        write(STDOUT_FILENO,line,n);
        printf("parent done");

    } else {
        // close(fd[1]);
        n = read(fd[0],line,MAXLINE);
        write(STDOUT_FILENO,line,n);
        char * msg = "hello parent\n";
        write(fd[1],msg,strlen(msg));
        TELL_PARENT(getppid());
        printf("child done");
    }
    return 0;
}
