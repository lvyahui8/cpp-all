#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>


void handle(int clientfd){	
	size_t n;
	char buf[1024];
	while((n = read(clientfd,buf,1024)) > 0 ){
		write(clientfd,buf,n);
	}

}

int main(){
	int listenfd,clientfd,handlerPid ;
	struct sockaddr_in localaddr ;
	// socket函数创建一个socket，socket可以认为是一个{lcoal_ip:local_port,remote_ip:remote_port}的四元组
	// AF_INET表示协议类似为：IPV4地址
	if((listenfd = socket(AF_INET,SOCK_STREAM,0)) < 0){
		printf("create socket failed.");	
		exit(1);
	}

	//  bind 实际就是填充socket的本地地址{local_ip:local_port}
	//  sockaddr 与 sockaddr_in 虽然是不同的结构体，但是同为16个字节的，并且结构并列,可以强制转换
	//  一般开发使用sockaddr_in 然后强制转换
	bzero(&localaddr,sizeof(localaddr));
	localaddr.sin_family = AF_INET;
	localaddr.sin_port = htons(9876);

	// inet_addr 已被废弃,改用inet_aton
	// localaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	inet_aton("127.0.0.1",& localaddr.sin_addr);	
	if(bind(listenfd,(struct sockaddr * ) &localaddr,sizeof(struct sockaddr)) < 0){
		printf("bind local_address and port failed.");	
		exit(1);
	}

	// listen 函数主要将套接字从默认的主动套接字转为被动套接字，并在内核中为次套接字分配TCP已连接和待连接队列,队列大小由listen函数第二个参数backlog指定
	if(listen(listenfd,2048) < 0){
		printf("listen failed.");
		exit(1);
	}
	
	for(;;){
		// accept函数阻塞等待从内核listenfd套接字对应的TCP已连接队列中获取新的已连接套接字，此套接字四元组已填满，要获取此套接字中的客户端地址，从accept的第二、第三参数中获取
		if((clientfd = accept(listenfd,NULL,NULL)) < 0){
			printf("accept failed.");	
			continue;
		}
		
		// 创建子进程处理请求
		//
		// close 函数实际是将套接字的引用计数减1，当一个套接字的引用计数为0时，套接字就会被真正的被删除
		if((handlerPid = fork()) == 0){
			// fork之后listenfd引用数增加1（多了一个进程持有），所以要close掉，handle进程也用不到
			close(listenfd);
			handle(clientfd);
			// 此时close才真正讲clientfd的引用数减少为0
			close(clientfd);
			exit(0);
		}
		// 此时只是关闭父进程对此套接字的引用，套接字依然被子进程持有（假设子进程的执行要慢一些，耗费一定时间），不会真正被删除
		close(clientfd);
		
	}

}

