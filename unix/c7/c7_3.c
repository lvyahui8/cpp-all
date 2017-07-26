#include <apue.h>
static void exit_handle1();
static void exit_handle2();

int main(int argc, char * argv[]){

    if(!atexit(exit_handle1))
        err_sys("can't register handle1");
    if(!atexit(exit_handle2))
        err_sys("can't register handle2");
    if(!atexit(exit_handle2))
        err_sys("can't register handle2");
    
    printf("main process is done");
    // return x == exit(x)
    // 1. invoke atexit
    // 2. close all stream
    // 3. invoke _exit , change to kernel
    return 0;
}

static void exit_handle1(){
    printf("handle1\n");
}

static void exit_handle2(){
    printf("handle2\n");
}
