#include <apue.h>
#include <error.h>
static void sig_alrm(int signo);

int main(int argc, char * argv[]){
	int n ;
	char line[MAXLINE];
	
	if (signal(SIGALRM,sig_alrm) == SIG_ERR){
		err_sys("signal(SIGALRM) error");	
	}
	// 10秒超时	
	alarm(10);
	
	if ((n = read(STDIN_FILENO,line,MAXLINE)) < 0 ){
		err_sys("read error");
	}
	// 一个进程只能有一个闹钟时间，调用alarm(0)将清除进程设置的闹钟	
	alarm(0);
	write(STDOUT_FILENO,line,n);

	return 0;
}

static void sig_alrm(int signo){
	// 什么都不做，将正常中断读操作
}
