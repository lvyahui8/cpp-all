#include <apue.h>
#include <sys/wait.h>
#include "c8_5_pr_exit.h"

int main(int argc, char * argv[]){
	pid_t	 pid;
	int status;

	if ((pid = fork()) < 0){
		err_sys("fork error");
	} else if (pid == 0){
		/* 子进程直接退出 */
		exit(7);
	}

	if (wait(&status) != pid){
		err_sys("wait error");
	}

	pr_exit(status);

	if ((pid = fork()) < 0){
		err_sys("fork error");
	} else if (pid == 0){
		/*子进程除0异常产生SIGFPE信号 */
	   status /= 0;
	}

	if (wait(&status) != pid){
		err_sys("wait error");
	}

	pr_exit(status);

	return 0;
}
