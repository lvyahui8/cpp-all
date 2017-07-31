#include <apue.h>
#include <sys/wait.h>


int main(int argc, char * argv[]){
    pid_t  pid;
    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (!pid) {
        /* chmod +x testinterp  */
        if (execl("/root/work/cpp-all/unix/c8/testinterp",
            "testinterp","arg1","arg2",(char * ) 0) < 0){
            err_sys("execl error");
        }
    }

    if (waitpid(pid, NULL,0 ) < 0){
        err_sys("waitpid error");
    }
    return 0;
}
