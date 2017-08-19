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

static void lockabyte(const char * name,int fd,off_t offset){
    if ( writew_lock(fd,offset,SEEK_SET,1) < 0 )
    {
        err_sys("%s: writew_lock error",name);
    }

    printf("%s: got the lock ,byte %lld\n",name ,(long long ) offset);
}

int main(int argc, char * argv[]){
    int fd;
    pid_t pid ;

    if( (fd = creat("templock",FILE_MODE)) < 0 )
    {
        err_sys("creat error");
    }

    if(write(fd,"ab",2)!= 2){
        err_sys("write error");
    }

    TELL_WAIT();

    // 此例子中，父进程等待获得子进程已取得的对某字节的锁，子进程也在等待获得父进程已取得的对某字节的锁
    // 所以出现死锁，系统会选择一个进程接收出错返回，具体哪个进程接收到出错信息是不一定的
    if((pid = fork()) < 0 )
    {
        err_sys("fork error");
    }
    else if(pid == 0 ){
        lockabyte("child",fd,0);
        TELL_PARENT(getppid());
        WAIT_PARENT();
        lockabyte("child",fd,1);
    } else {
        lockabyte("parent", fd ,1);
        TELL_CHILD(pid);
        WAIT_CHILD();
        lockabyte("parent",fd,0);
    }
	return 0;
}
