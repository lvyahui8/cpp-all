#include <apue.h>
#include <unistd.h>

static void charatatime(char *);
/* 进程改为串行 */
int main(int argc, char * argv[]){
    pid_t  pid;

    TELL_WAIT();

    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (!pid){
        WAIT_PARENT();
        charatatime("output from child\n");
    } else {
        charatatime("output from parent\n");
        TELL_CHILD(pid);
    }

    return 0;
}

static void charatatime(char * str) {
    char * ptr;
    int c;

    setbuf(stdout,NULL);

    for (ptr = str; (c = * ptr++); ) {
        usleep(10);
        putc(c,stdout);
    }
}
