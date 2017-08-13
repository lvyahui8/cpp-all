#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <syslog.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <sys/stat.h>

#define LOCKFILE "/var/run/daemon.pid"
#define LOCKMODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)


int lockfile1(int fd)
{
	struct flock fl;

	fl.l_type = F_WRLCK;
	fl.l_start = 0;
	fl.l_whence = SEEK_SET;
	fl.l_len = 0;
	return(fcntl(fd, F_SETLK, &fl));
}

int already_running1(){
	int fd;
	char buf[16];
	
	fd = open(LOCKFILE,O_RDWR | O_CREAT ,LOCKMODE);
	
	if ( fd < 0) {
		syslog(LOG_ERR, "can't open %s: %s" , LOCKFILE,strerror(errno));
		exit(1);
	}
		
	if ( lockfile1(fd) < 0) {
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

int main(int argc, char * argv[]){
	if (already_running1()){
		printf("peoccesss is running");
		return 1;
	}
	printf("hello");
	return 0;
}
