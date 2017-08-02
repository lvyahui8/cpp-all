#include <apue.h>
static void sig_user(int);

int main(int argc, char * argv[]){
    if (signal(SIGUSR1,sig_user) == SIG_ERR)
    {
        err_sys("can't catch SIGUSR1");
    }

    if (signal(SIGUSR2,sig_user) == SIG_ERR)
    {
        err_sys("can't catch SIGUSR2");
    }

    for(;;){
        pause();
    }
	return 0;
}

static void sig_user(int signo){
    if (signo == SIGUSR1){
        printf("reveived SIGUSR1\n");
    } else if(signo == SIGUSR2){
        printf("received SIGUSR2\b");
    } else {
        err_dump("reveived signal %d\n",signo);
    }
}
