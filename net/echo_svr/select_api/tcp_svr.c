#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>


int main(){
	int listenfd,clientfd;
	struct sockaddr_in localaddr ;

	int i ,n,maxcli,maxfd,sockfd,nready;
	int client[FD_SETSIZE];
	fd_set rset,allset;
	char buf[1024];

	if((listenfd = socket(AF_INET,SOCK_STREAM,0)) < 0){
		printf("create socket failed.");	
		exit(1);
	}

	bzero(&localaddr,sizeof(localaddr));
	localaddr.sin_family = AF_INET;
	localaddr.sin_port = htons(9876);

	inet_aton("127.0.0.1",& localaddr.sin_addr);	
	if(bind(listenfd,(struct sockaddr * ) &localaddr,sizeof(struct sockaddr)) < 0){
		printf("bind local_address and port failed.");	
		exit(1);
	}

	if(listen(listenfd,2048) < 0){
		printf("listen failed.");
		exit(1);
	}
 	maxfd = listenfd;
	for(i = 0 ; i < FD_SETSIZE; i++){
		client[i] = -1;
	}
	FD_ZERO(&allset);
	FD_SET(listenfd,&allset);

	for(;;){
		rset = allset;
		nready = select(maxfd + 1,&rset,NULL,NULL,NULL);
		if(FD_ISSET(listenfd,&rset)){
			// 有新的连接进来
			clientfd = accept(listenfd,NULL,NULL);

			for(i = 0 ; i < FD_SETSIZE; i ++){
				if(client[i] < 0){
					client[i] = clientfd;
					break;
				}
			}	
			if(i == FD_SETSIZE){
				printf("too many clients");
				exit(1);
			}
			FD_SET(clientfd,&allset);
			if(clientfd > maxfd){
				maxfd = clientfd;
			}

			if(i > maxcli){
				maxcli = i ;
			}

			if(--nready <= 0){
				continue;
			}
		}
		
		for(i = 0 ; i <= maxcli;i ++){
			if((sockfd = client[i]) < 0 ){
				continue;
			}

			if(FD_ISSET(sockfd,&rset)){
				if((n = read(sockfd,buf,1024)) == 0){
					close(sockfd);
					FD_CLR(sockfd,&allset);
					client[i] = -1;
				}else {
					write(sockfd,buf,n);
				}
				
				if(-- nready <= 0){
					break;
				}
			}
		}	
		
	}

}

