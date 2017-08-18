#include <stdio.h>
#include <syslog.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/resource.h>

#define PID_FILE "/var/run/sampled.pid"

int sampled_running(){
    FILE * pidfile = fopen(PID_FILE,"r");
    pid_t pid;
    int ret ;

    if (! pidfile) {
        return 0;
    }

    ret = fscanf(pidfile,"%d",&pid);
    if (ret == EOF && ferror(pidfile) != 0){
        syslog(LOG_INFO,"Error open pid file %s",PID_FILE);
    }

    fclose(pidfile);

    if ( kill(pid , 0 ) ){
        syslog(LOG_INFO,"Remove a zombie pid file %s", PID_FILE);
        unlink(PID_FILE);
        return 0;
    }

    return pid;
}

pid_t sampled(){
    pid_t pid;
    struct rlimit rl;
    int fd,i;

    // 创建子进程，并退出当前父进程
    if((pid = fork()) < 0){
        syslog(LOG_INFO,"sampled : fork error");
        return -1;
    }
    if ( pid != 0) {
        //  父进程直接退出
        exit(0);
    }

    // 新建会话，成功返回值是会话首进程id，进程组id ，首进程id
    pid = setsid();

    if ( pid < -1 ){
        syslog(LOG_INFO,"sampled : setsid error");
        return -1;
    }

    // 将工作目录切换到根目录
    if ( chdir("/") < 0 ) {
        syslog(LOG_INFO,"sampled : chidr error");
        return -1;
    }

    // 关闭所有打开的句柄，如果确定父进程未打开过句柄，此步可以不做
    if ( rl.rlim_max == RLIM_INFINITY ){
        rl.rlim_max = 1024;
    }
    for(i = 0 ; i < rl.rlim_max; i ++) {
        close(i);
    }

    fd = open("/dev/null",O_RDWR,0);
    if(fd != -1){
        dup2(fd,STDIN_FILENO);
        dup2(fd,STDOUT_FILENO);
        dup2(fd,STDERR_FILENO);
        if (fd > 2){
            close(fd);
        }
    }

    umask(0);
    return 0;
}

int pidfile_write(){
    // 这里不用fopen直接打开文件是不想创建666权限的文件
    FILE * pidfile = NULL;
    int pidfilefd = creat(PID_FILE,S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if(pidfilefd != -1){
        pidfile = fdopen(pidfilefd,"w");
    }

    if (! pidfile){
        syslog(LOG_INFO,"pidfile write : can't open pidfile:%s",PID_FILE);
        return 0;
    }
    fprintf(pidfile,"%d",getpid());
    fclose(pidfile);
    return 1;
}

int main(){
    int err,signo;
    sigset_t mask;

    if (sampled_running() > 0 ){
         exit(0);
    }

    if ( sampled() != 0 ){

    }

    if (pidfile_write() <= 0) {
        exit(0);
    }

    while(1) {
        err = sigwait(&mask,&signo);
        if( err != 0  ){
            syslog(LOG_INFO,"sigwait error : %d",err);
            exit(1);
        }
		switch (signo){
			default :
				syslog(LOG_INFO,"unexpected signal %d \n",signo);
				break;
			case SIGTERM:
				syslog(LOG_INFO,"got SIGTERM. exiting");
				exit(0);
		}

    }

}
