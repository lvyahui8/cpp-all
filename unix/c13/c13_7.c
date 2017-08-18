#include <pthread.h>
#include <apue.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <syslog.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/resource.h>


#define LOCKFILE "/var/run/daemon.pid"
#define LOCKMODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

int lockfile(int fd)
{
	struct flock fl;

	fl.l_type = F_WRLCK;
	fl.l_start = 0;
	fl.l_whence = SEEK_SET;
	fl.l_len = 0;
	return(fcntl(fd, F_SETLK, &fl));
}

int already_running(){
	int fd;
	char buf[16];

	fd = open(LOCKFILE,O_RDWR | O_CREAT ,LOCKMODE);

	if ( fd < 0) {
		syslog(LOG_ERR, "can't open %s: %s" , LOCKFILE,strerror(errno));
		exit(1);
	}

	if ( lockfile(fd) < 0) {
		if (errno == EACCES || errno == EAGAIN ){
			close(fd);
			return 1;
		}
		syslog(LOG_ERR,"can't lock %s : %s" , LOCKFILE,strerror(errno));
		exit(1);
	}

	// 文件长度截断为0 ，相当于清空文件
	ftruncate(fd,0);

	// 写入进程pid 锁文件
	sprintf(buf,"%ld",(long) getpid());
	write(fd,buf,strlen(buf) + 1);

	return 0;
}


void daemonize(const char * cmd){
	int 		i, fd0,fd1,fd2;
	pid_t		pid;
	struct rlimit 	rl;
	struct sigaction sa;

	// 取消进程的文件掩码设置，防止子进程创建文件权限不正确	
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



sigset_t mask;


void reload(void){
	// 在这里面重新读取配置
}


// 此线程专门处理信号
void * thr_fn(void * arg){
	int err, signo;

	for (;;){
		// 不断等待信号
		err = sigwait(&mask,&signo);
		if ( err != 0 ) {
			syslog(LOG_ERR,"sigwait failed");
			exit(1);
		}

		switch (signo){
			default :
				syslog(LOG_INFO,"unexpected signal %d \n",signo);
				break;
			case SIGHUP:
				syslog(LOG_INFO, "Re-reading configuration file");
				reload();
				break;
			case SIGTERM:
				syslog(LOG_INFO,"got SIGTERM. exiting");
				exit(0);
		}
	}
	return 0;

}


int main(int argc, char * argv[]){
	int err;
	pthread_t tid;
	char * cmd;
	struct sigaction sa;

	if ( ( cmd = strrchr(argv[0],'/' )) == NULL){
		cmd = argv[0];
	}else  cmd ++;

	daemonize(cmd);

	if(already_running()){
		syslog(LOG_ERR,"daemon already running");
		exit(1);
	}

	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;

	if (sigaction (SIGHUP , &sa,NULL) < 0){
		err_quit("%s : cant't restore SIGHUP default");
	}
	sigfillset(&mask);
	if ((err = pthread_sigmask(SIG_BLOCK,&mask,NULL)) != 0 ){
		err_exit(err,"SIG_BLOCK error");
	}

	err = pthread_create(&tid,NULL,thr_fn,0);
	if ( err != 0 ) {
		err_exit(err,"can't create thread");
	}
	
	pthread_exit(NULL);
	return 0;	

}
