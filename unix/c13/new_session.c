#include <apue.h>

int main(int argc, char * argv[]){
    pid_t pid ;
    if ((pid = fork()) < 0){
        err_quit("can't fork");
    }else {
        exit(0);
    }
    if(setsid() < 0){
        err_quit("can't setsid");
    }
    pause();
	return 0;
}
