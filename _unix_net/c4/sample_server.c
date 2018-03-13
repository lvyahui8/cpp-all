#include <sys/socket.h>

int main(){
	int listenfd = socket(AF_INET,SOCK_STREAM,IPPROTO_CP);

	if(listenfd <= 0 ){

	}

	socklen_t len;
	struct sockaddr_in servaddr, cliaddr;
	char buff[1024];

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(13);
	
	if(! bind(listenfd,&servaddr,sizeof(servaddr))){
			
	}	

	if(! listen(listenfd,1024)){
	
	}
	
	for(;;){
		len = sizeof(cliaddr);
		confd = accept(listenfd,&cliaddr, &len);
		if(confd <= 0){
			continue;
		}		

		time_t ticks;
		ticks = time(NULL);
		snprintf(buff,sizeof(buff),"%.24s\n",ctime(&ticks));
		write(connfd,buff,strlen(buff);
		close(connfd);
	}
	return 0;
}
