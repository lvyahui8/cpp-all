#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#define UNIXSTR_PATH "/tmp/unix.str"
#define LISTENQ 5
#define BUFFER_SIZE 256

int main(void)
{
    int listenfd, connfd;
    socklen_t len,addrlen;
    struct sockaddr_un servaddr, cliaddr;
    char  * sockname = "localsock";
    if(-1 == (listenfd = socket(AF_LOCAL, SOCK_STREAM, 0)))
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    unlink(UNIXSTR_PATH);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sun_family = AF_UNIX;
    // 如果sun_path是普通路径名，则会bind函数会创建本地socket文件， lsof可以看到进程打开了文件,进程退出前需要调用unlink删除此文件
    // unix_doma 2407 root    3u  unix 0x0000000073757b6b      0t0   57793 /tmp/unix.str type=STREAM
    // strcpy(servaddr.sun_path, UNIXSTR_PATH);
    // 如果sun_path是抽象路径明，则sun_path的第一个字节必须为NULL('\0'),这是不会创建文件
    // 直接赋值，则抽象路径名是一个乱码
    // 按下面的代码，可以看到套接字
    // unix_doma 3027 root    3u  unix 0x00000000d25d7280      0t0   89075 @localso type=STREAM
    servaddr.sun_path[0] = '\0';
    strcpy(servaddr.sun_path + 1,sockname);
    addrlen = sizeof(servaddr.sun_family) + sizeof(sockname); 
    if(-1 == bind(listenfd, (struct sockaddr *)&servaddr, addrlen))
    {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    listen(listenfd, LISTENQ);

    len = sizeof(cliaddr);

    if(-1 == (connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &len)))
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    char buf[BUFFER_SIZE];

    while(1)
    {
        bzero(buf, sizeof(buf));
        if(read(connfd, buf, BUFFER_SIZE) == 0) break;
        printf("Receive: %s", buf);
    }

    close(listenfd);
    close(connfd);
    unlink(UNIXSTR_PATH);

    return 0;
}
