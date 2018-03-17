#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>

void write2svr(int svrfd){
	char line[1024];
	char recv[1024];
	while(fgets(line,1024,stdin) != NULL){
		write(svrfd,line,strlen(line));
		if(read(svrfd,recv,1024) <= 0){
			printf("recv failed.");
			exit(1);
		}
		puts(recv);
	}

}
int main(){
	int svrfd ;
	struct sockaddr_in svraddr;
	char * svrIp = "127.0.0.1";

	svrfd = socket(AF_INET,SOCK_STREAM,0);	
	bzero(&svraddr,sizeof(svraddr));
	svraddr.sin_family = AF_INET;
	svraddr.sin_port = htons(9876);
	inet_aton(svrIp,& svraddr.sin_addr);

	if(connect(svrfd,(struct sockaddr *) & svraddr,sizeof(struct sockaddr)) < 0 ){
		printf("connect failed.");
		exit(1);
	}

	write2svr(svrfd);

	return 0;
}
