#include <apue.h>
#include <sys/wait.h>
/*
 * 希望父进程结束之后，子进程继续运行，并且子进程不会成为僵尸进程，方法是创建孙子进程
 * */
int main(int argc, char * argv[]){
    pid_t  pid;
    if ((pid = fork()) < 0){
        err_sys("fork error");
    } else if (pid == 0) {
        /* 第一个子进程 */
        if ((pid = fork()) < 0){
            err_sys("fork error");
        } else if(pid > 0){
            /*
             * 第一个子进程直接退出
             * 其退出之后，其创建的子进程已经被init进程接管
             * */
            exit(0);
        }
        /* 孙子进程继续运行 */
        sleep(15);
        printf("second child , parent pid = %ld \n",(long) getppid());
        exit(0);
    }
    /* 只等待儿子进程结束 */
    if (waitpid(pid,NULL,0) != pid){
        err_sys("waitpid error");
    }
    sleep(10);
    exit(0);
}
