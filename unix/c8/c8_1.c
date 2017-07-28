#include <apue.h>
int globvar = 6;
char buf[] = "a write to stdout\n";
// 可以对程序的输出进行重定向，可以发现：在重定向父进程的标准输出时，子进程的标准输出也被重定向
// 最主要的：父进程与子进程共享同一个文件偏移量
int main(int argc, char * argv[]){
	int var ;		
	pid_t pid;
	
	var = 80;
	
	if (write(STDOUT_FILENO,buf,sizeof(buf) -1) != sizeof(buf) - 1){
		err_sys("write error");
	}
	
	if (pid = fork() < 0) {
		err_sys("fork error");
	} else if (!pid) {
		globvar++;
		var++;
	} else {
		sleep(2);
	}
	printf("pid = %ld, glob = %d,var = %d\n",(long)getpid(),globvar,var);
	return 0;
}
