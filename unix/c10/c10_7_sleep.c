#include <apue.h>
#include <unistd.h>

static void sig_alrm(int signo){
	
}

unsigned int sleep1(unsigned int seconds){
	if(signal(SIGALRM,sig_alrm) == SIG_ERR){
		return seconds;
	}
	alarm(seconds);
	// 如果在调用pause之前，alarm设置的时间就已经超时，则在此之后pause，即使有alrm信号产生，程序也将被永远挂起
	pause();
	return alarm(0);
}

int main(int argc, char * argv[]){
	printf("hello apue");
	return 0;
}
