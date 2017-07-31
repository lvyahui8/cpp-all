#include <apue.h>
#include <errno.h>
#include <unistd.h>
#include <wait.h>

int system(const char * cmdstr){
    pid_t  pid;
    int status = 0;

    if (cmdstr == NULL){
        return 1;
    }

    if ((pid = fork()) < 0){
        status = -1;
    } else if (pid == 0){
        execl("/bin/sh","sh","-c",cmdstr,(char * )0);
        /* execl error*/
        _exit(127);
    } else {
        while(waitpid(pid,&status,0) < 0){
            if (errno != EINTR){
                status = -1;
                break;
            }
        }
    }

    return status;
}

int main(int argc, char * argv[]){
    int status;
    if ((status = system("date")) < 0){
        err_sys("system() error");
    }

    pr_exit(status);

    if ((status = system("nosuchcommand")) < 0){
        err_sys("system() error");
    }

    pr_exit(status);

    if ((status = system("who;exit 44")) < 0){
        err_sys("system() error");
    }

    pr_exit(status);
    return 0;
}
