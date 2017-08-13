#include <apue.h>
#include <syslog.h>
#include <fcntl.h>
#include <sys/resource.h>

// ymm install rsyslog -y
//
void daemonize(const char * cmd){
	int 		i, fd0,fd1,fd2;
	pid_t		pid;
	struct rlimit 	rl;
	struct sigaction sa;
	
	umask(0); // chmod 000
	
	if (getrlimit(RLIMIT_NOFILE, &rl) < 0 ){
		err_quit("%s : can't get file limit ", cmd);
	}
	
	if ((pid = fork()) < 0){
		err_quit("%s : cant't fork ",cmd);
	} else if ( pid != 0 ){
		// 父进程直接结束
		// shell 会话会认为这条命令已经执行完成
		exit(0);
	}

	// 创建一个新的会话	
	// 并使此子进程成为一个新的进程组的组长
	// 断开所有控制终端
	// 简而言之：setsid使该进程成为一个没有控制终端的会话首进程
	setsid();
	
	// 清空原来的信号集
	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	
	sa.sa_flags = 0;

	if ( sigaction(SIGHUP,&sa,NULL) < 0) {
		err_quit("%s : cant't ignore SIGHUP",cmd);
	}
	
	// 继续fork 是为了兼容System V系统，保证该守护进程不是会话首进程，
	// 这样在System V系统中，才不会取得任何控制终端，//
	// 否则在System V系统中，还是会给会话首进程分配控制终端	
	if ( (pid = fork()) < 0 ){
		err_quit("%s : can't fork ",cmd);
	} else if( pid != 0) {
		// 父进程直接结束
		exit(0);	
	}
	
	// 切换工作目录到根目录，防止占用挂载的设备导致设备不能卸载
	if( chdir("/") < 0 ) {
		err_quit("");
	}

	//  关闭所有打开的文件句柄，以防止有继承父进程打开的文件句柄	
	if(rl.rlim_max == RLIM_INFINITY) // 无穷大值
		rl.rlim_max = 1024;	
	for ( i = 0 ; i < rl.rlim_max ; i ++ ){
		close(i);
	}

	// 文件描述符 0 1 2 （stdin、stdout、stderr）
	fd0 = open("/dev/null",O_RDWR);
	// dup 函数创建一个新的文件描述符，值为当前可用文件句柄的最小值，所以这里是1
	fd1 = dup(0);
	fd2 = dup(0);
	
	openlog(cmd, LOG_CONS,LOG_DAEMON);

	if( fd0 != 0 || fd1 != 1 || fd2 != 2 ){
		syslog(LOG_ERR,"unexpected file descriptors %d %d %d",
			fd0,fd1,fd2);
		exit(1);
	}			
}

/*
 * ？ 表示没有控制终端
 * 也可以看到没有id为5653 的进程。表示此进程是被init接管的一个孤儿进程
 * ➜  c13 git:(master) ✗ ./c13_1.app 
 * ➜  c13 git:(master) ✗ ps -ajfx | grep c13_1.app
 *     1  5655  5653  5653 ?           -1 S        0   0:00 ./c13_1.app
 * ➜  c13 git:(master) ✗ ps axu | grep 5653
 * ➜  c13 git:(master) ✗ 
 *
 */
int main(int argc, char * argv[]){	
	daemonize("top");	
	sleep(1000);
	return 0;
}
