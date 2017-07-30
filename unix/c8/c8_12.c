#include <apue.h>
#include <unistd.h>

static void charatatime(char *);

int main(int argc, char * argv[]){
    pid_t  pid;
    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (!pid){
        charatatime("output from child\n");
    } else {
        charatatime("output from parent\n");
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
