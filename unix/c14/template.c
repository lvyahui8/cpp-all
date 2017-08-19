#include <apue.h>
#include <fcntl.h>

int lock_reg(int fd,int cmd,int type,off_t offset ,int whence,off_t len){
    struct flock lock;

    lock.l_type = type;
    lock.l_start = offset;
    lock.l_whence = whence;
    lock.l_len = len;

    return (fcntl(fd,cmd,&lock));
}

pid_t lock_test (int fd,int type ,off_t offset,int whence,off_t len){
    struct flock lock;

    lock.l_type = type;
    lock.l_start = offset;
    lock.l_whence = whence;
    lock.l_len = len;

    if(fcntl (fd,F_GETLK,&lock) < 0){
        err_sys("fcntl error");
    }

    if (lock.l_type == F_UNLCK){
        return 0;
    }

    return lock.l_pid;
}

// 在整个文件上加写锁
int lockfile(int fd){
    struct flock fl;
    fl.l_type = F_WRLCK;
    fl.l_start = 0 ;
    fl.l_whence = SEEK_SET;
    fl.l_len = 0;   //  len 为0 表示从起始开始无穷远，结合start 0 即表示整个文件
    return fcntl(fd,F_SETLK,&fl);
}

int main(int argc, char * argv[]){
	printf("hello apue");
	return 0;
}
