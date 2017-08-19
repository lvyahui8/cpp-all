#include <apue.h>
#include <string.h>
#include <sys/wait.h>

/*
 * 一个管道的双工通信，实际这种方式有两个地方不好
 * 1、为了防止进程写了之后自己有立马读，必须等待另一个进程先读，就把进程做成同步了
 * 2、同一时刻只能往一个方向写数据
 * 所以，还是c15_5.c中的用两个管道来做两个进程间的双工通信要更好
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
        waitpid(pid,NULL,0);
        n = read(fd[0],line,MAXLINE);
        write(STDOUT_FILENO,line,n);
        printf("parent done");

    } else {
        n = read(fd[0],line,MAXLINE);
        write(STDOUT_FILENO,line,n);
        char * msg = "hello parent\n";
        write(fd[1],msg,strlen(msg));
        printf("child done");
    }
    return 0;
}
