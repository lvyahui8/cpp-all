#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#define UNIXDG_PATH "/tmp/unix.dg"
#define BUFFER_SIZE 256

int main(void)
{
    int sockfd;
    struct sockaddr_un servaddr, cliaddr;

    sockfd = socket(AF_LOCAL, SOCK_DGRAM, 0);

    unlink(UNIXDG_PATH);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sun_family = AF_LOCAL;
    strcpy(servaddr.sun_path, UNIXDG_PATH);
    // 创建的类似与udp的unix域套接字
    // unix_doma 3243 root    3u  unix 0x0000000042ef8626      0t0   94397 /tmp/unix.dg type=DGRAM
    bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    socklen_t len = sizeof(cliaddr);
    char buf[BUFFER_SIZE];

    while(1)
    {
        bzero(buf, BUFFER_SIZE);

        if(0 == recvfrom(sockfd, buf, BUFFER_SIZE, 0, (struct sockaddr *)&cliaddr, &len))
        {
            break;
        }
        printf("recvfrom: %s", buf);
    }

    close(sockfd);
    unlink(UNIXDG_PATH);

    return 0;
}
