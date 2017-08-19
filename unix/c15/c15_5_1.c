#include <apue.h>
#include <string.h>

/*
 * 此程序输出
 * ➜  c15 git:(master) ✗ ./c15_5_1.app
 * hello child
 * parent done#
 * 原因很简单，全部操作都在 父进程完成了(父进程写完立即读)，子进程卡在了read上
 * 这里就存在竞态条件，如果父进程write之后恰好子进程read，就正常
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
        // 如果一端关闭一个句柄，则通道将变成只能固定单向传递
        // 不一定要关闭，只是习惯让管道单向通信。管道同时间也只能单向通信，所以叫半双工
        //close(fd[0]);
        char * msg = "hello child\n";
        write(fd[1],msg,strlen(msg));
        n = read(fd[0],line,MAXLINE);
        write(STDOUT_FILENO,line,n);
        printf("parent done");

    } else {
        // close(fd[1]);
        n = read(fd[0],line,MAXLINE);
        write(STDOUT_FILENO,line,n);
        char * msg = "hello parent\n";
        write(fd[1],msg,strlen(msg));
        printf("child done");
    }
    return 0;
}
