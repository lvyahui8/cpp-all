#include <apue.h>
#include <pthread.h>

//
// 线程实际是平级的，没有可以说没有主次之分。
// 平时写的代码，main方法所在线程return之后，并没立即结束，后面进一步调用了exit系统调用，所有整个进程都会退出
// 所以在开发者看来，有主次之分，主的退出了，子的自然跟着退出了
// 实际上。只要修改main线程的行为，直接结束掉线程，那么其余的线程，并不会退出
//

void * uthread(){
	while(1){
		printf("is live\n");
		sleep(1);
	}	
	return ((void *)0);
}
/*
 * ➜  c11 git:(master) ✗ ./thread_exit.app 
 * pid:12142
 * is live
 * is live
 * is live
 * is live
 * ...
 *
 * 可以看到main所在线程已经退出，但是新的线程依然在运行，进程依然存在
 * ➜  ~ ps -lL -p 12142 
 * F S   UID   PID  PPID   LWP  C PRI  NI ADDR SZ WCHAN  TTY          TIME CMD
 * 0 Z     0 12142  5029 12142  0  80   0 -     0 exit   pts/0    00:00:00 thread_exit.app <defunct>
 * 1 S     0 12142  5029 12143  0  80   0 -  4197 hrtime pts/0    00:00:00 thread_exit.app
 *
 */
int main(int argc, char * argv[]){
	pthread_t u_tid;
	int err ;
	printf("pid:%d\n",getpid());
	err = pthread_create(&u_tid,NULL,uthread,NULL);
	if(err != 0){
		err_exit(err,"can't create thread");
	}	
	pthread_exit(NULL);
	return 0;
}
