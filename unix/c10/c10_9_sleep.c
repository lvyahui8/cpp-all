#include <apue.h>
#include <unistd.h>
#include <setjmp.h>

static jmp_buf env_alrm;

static void sig_alrm(int signo){
	printf("longjmp\n");
	longjmp(env_alrm,1);	
}

unsigned int sleep2(unsigned int seconds){
	if(signal(SIGALRM,sig_alrm) == SIG_ERR){
		return seconds;
	}
	// 这个程序的特点是，只要有alrm信号产生，则程序会回到sejmp函数，并返回1，故程序会正常退出
	// pause 被中断之后，程序实际去处理SIGINT信号去了（在运行sig_int函数）
	// 而当时钟到达时，SIGALRM处理程序调用longjmp，重置执行流，程序继续运行将退出，可以看到sig_int提前结束了
	if(setjmp(env_alrm) == 0 ){
		alarm(seconds);
		// pause 使得进程挂起直到捕捉到一个信号，所以任意一个信号都都可以是pause结束，并不仅仅是SIGALRM
		pause();
	}	
	return alarm(0);
}

static void sig_int(int);
/*
 * 运行输出（键如中断字符产生SIGINT信号来中断pause休眠）
 * ➜  c10 git:(master) ✗ ./c10_9_sleep.app 
 * ^C
 * sig_int starting
 * sleep2 returned: 0
 */
int main(int argc, char * argv[]){
	unsigned int unslept;
	if (signal(SIGINT,sig_int) == SIG_ERR) {
		err_sys("signal(SIGINT) error");	
	}
	unslept = sleep2(5);
	printf("sleep2 returned: %u\n",unslept);
	return 0;
}

static void sig_int(int signo){
	int i , j;
	volatile int k;
	
	printf("\nsig_int starting\n");
	for ( i = 0 ; i < 300000; i ++)
	{
		for ( j = 0 ; i < 4000; j ++)
			k += i * j ;
	}
	printf("sig_int finished\n");
}
