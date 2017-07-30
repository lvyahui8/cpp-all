#include <apue.h>
#include <sys/wait.h>

char * env_init [] = {
        "USER=lvyahui",
        "PATH=/tmp",
        NULL
};

int main(int argc, char * argv[]){
    pid_t  pid;
    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (!pid) {
        if (execle("/root/work/cpp-all/net/exe_get_example","exe_get_example","arg1","arg2"
            , (char *) 0, env_init) < 0) {
            err_sys("execle error");
        }
    }

    if (waitpid(pid, NULL,0 ) < 0){
        err_sys("wait error");
    }

    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (!pid) {
        if (execlp("exe_c8_13","exe_c8_13","arg1", (char *) 0) < 0) {
            err_sys("execlp error");
        }
    }
    return 0;
}
