#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <limits.h>
#include <poll.h>
#include <errno.h>


int main(){
	int listenfd,sockfd,connfd;
	struct sockaddr_in localaddr ;
	int nready,i,maxcli;
	ssize_t n;
	char buf[1024];
	struct pollfd client[FOPEN_MAX];

	if((listenfd = socket(AF_INET,SOCK_STREAM,0)) < 0 ){
		printf("create socket failed.");
		exit(1);
	}

	
	bzero(&localaddr,sizeof(localaddr));

	localaddr.sin_family = AF_INET;
	localaddr.sin_port = htons(9876);

	inet_aton("127.0.0.1",& localaddr.sin_addr);

	if((bind(listenfd,(struct sockaddr *) &localaddr,sizeof(struct sockaddr)) < 0)){
		printf("bind failed.");
		exit(1);
	}

	if(listen(listenfd , 2048) < 0){
		printf("listen failed.");
		exit(1);
	}

	// 描述符数组第一个元素放监听套接字
	client[0].fd = listenfd;
	client[0].events = POLLRDNORM;

	for (i = 1; i < FOPEN_MAX; i ++){
		client[i].fd = -1; // 表示未放置任何套接字
	}

	maxcli = 0;

	for(;;){
		// -1 : INFTIM 表示永远等待下去，只到有句柄发生变化
		nready = poll(client,maxcli + 1, -1);

		if(client[0].revents & POLLRDNORM){
			// 新的客户连接
			connfd = accept(listenfd,NULL,NULL);
			// 找一个空位放置连接
			for(i = 0; i < FOPEN_MAX; i++){
				if(client[i].fd < 0 ){
					client[i].fd = connfd;
					break;
				}
			}

			if(i == FOPEN_MAX){
				printf("too many clients");
				continue;
			}

			client[i].events = POLLRDNORM;

			if( i > maxcli){
				maxcli = i;
			}

			if( --nready <=0){
				continue;
			}
		}

		for(i = 1 ; i <= maxcli; i++){
			if((sockfd = client[i].fd) < 0){
				continue;
			}

			if(client[i].revents & (POLLRDNORM | POLLERR)){
				if((n = read(sockfd,buf,1024)) < 0){
					if(ECONNRESET == errno){
						// 客户端关闭连接
						close(sockfd);
						client[i].fd = -1;
					} else {
						printf("read error");
					}
				} else if(0 == n){
					// 客户端关闭连接
					close(sockfd);
					client[i].fd = -1;
				} else {
					write(sockfd,buf,n);
				}
				
				if(--nready <= 0 ){
					break;
				}
			}
				
		}
	}
	
}



















