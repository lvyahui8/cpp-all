#include <apue.h>
#include <unistd.h>
#include <setjmp.h>

static jmp_buf env_alrm;

static void sig_alrm(int signo){
	longjmp(env_alrm,1);	
}

unsigned int sleep2(unsigned int seconds){
	if(signal(SIGALRM,sig_alrm) == SIG_ERR){
		return seconds;
	}
	// 这个程序的特点是，只要有alrm信号产生，则程序会回到sejmp函数，并返回1，故程序会正常退出
	// 但是，longjmp强制让程序执行流回到setjmp而且任意一个信号都可能使得pause结束，这带来一些新的问题
	if(setjmp(env_alrm) == 0 ){
		alarm(seconds);
		pause();
	}	
	return alarm(0);
}

int main(int argc, char * argv[]){
	printf("hello apue");
	return 0;
}
