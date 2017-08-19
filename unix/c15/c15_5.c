#include <apue.h>
#include <string.h>
#include <sys/wait.h>
/*
 * 正常输出，全双工通信
 * ➜  c15 git:(master) ✗ ./c15_5.app
 * hello child
 * hello parent
 * parent done
 * child done
 *
 */
int main(int argc, char * argv[]){
    int n;
    int tochfd[2];
    int topafd[2];

    pid_t pid;
    char line[MAXLINE];

    if ((pipe(tochfd) <0 )){
        err_sys("pipe error");
    }
    if ((pipe(topafd) <0 )){
        err_sys("pipe error");
    }

    // 下面的close操作都不是必须的
    if((pid = fork()) < 0){
        err_sys("fork error");
    } else if ( pid > 0  )
    {
        // 关闭从子进程的读端
        close(tochfd[0]);
        char * msg = "hello child\n";
        write(tochfd[1],msg,strlen(msg));
        // 关闭向父进程的写端，（自己向自己写用不着管道）
        close(topafd[1]);
        n = read(topafd[0],line,MAXLINE);
        write(STDOUT_FILENO,line,n);

       // waitpid(pid,NULL,0);
        printf("parent done\n");
    } else {
        // 关闭向子进程的写端
        close(tochfd[1]);
        n = read(tochfd[0],line,MAXLINE);
        write(STDOUT_FILENO,line,n);
        // 关闭从父进程的读端
        close(topafd[0]);
        char * msg = "hello parent\n";
        write(topafd[1],msg,strlen(msg));

        printf("child done\n");
    }
    return 0;
}
