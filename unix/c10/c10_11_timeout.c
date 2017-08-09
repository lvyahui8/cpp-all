#include <apue.h>
#include <error.h>
#include <setjmp.h>

static void sig_alrm(int signo);
static jmp_buf env_alrm;
/**
 * 运行输出
 * ➜  c10 git:(master) ✗ ./c10_11_timeout.app 
 * h
 * h
 * ➜  c10 git:(master) ✗ ./c10_11_timeout.app
 * read timeout!
 *
 */
int main(int argc, char * argv[]){
	int n ;
	char line[MAXLINE];
	
	if (signal(SIGALRM,sig_alrm) == SIG_ERR){
		err_sys("signal(SIGALRM) error");	
	}
	if (setjmp(env_alrm) != 0){
		err_quit("read timeout!");
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
	// 直接将执行流重置到setjmp，将进一步调用err_quit正退出
	// 可以防止某些系统自动重启动被中断的系统调用（read函数）
	longjmp(env_alrm,1);
}
