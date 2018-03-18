#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/select.h>
#include <math.h>

// #define max(x,y) ((x) > (y) ? (x) : (y))
// 上述max宏处理max(x++,y)之类的结果不对

#define max(x,y) ({	\
		typeof(x) __x = (x);	\
		typeof(y) __y = (y);	\
		(void)(&__x == &__y);	\
		__x > __y ? __x : __y;})

void write2svr(int svrfd){
	char line[1024];
	char recv[1024];
	int maxfdp1;
	fd_set rset;
	FD_ZERO(&rset);
	for(;;){
		// 关心标准输入和套接字输入
		FD_SET(fileno(stdin),&rset);
		FD_SET(svrfd,&rset);
		// fd_set 一般用位来表示描述符,而实际fd_set一般为整形数组
		// 那么在32位系统上
		// a[0]则表示了描述符0-31的状态
		// a[1]则表示了描述符32-63的状态
		// ....依此类推
		// fd_set默认有1024位来表示描述0-1023的状态，用整形数组来存储，也是因为没有一个基础变量有如此多位
		// maxfdp1则告诉内核扫描到最大多少位即可,所以一般是最大描述符+1
		// 也就是说从0,1,2....maxfdp1-1，这些描述符都会被检测，并且通过将对应位从0修改为1来表示描述服状态改变
		// 所以如果要检测一个描述符的读、写、异常状态，则应该传入三个fd_set给select
		maxfdp1 = max(fileno(stdin),svrfd) + 1;
		select(maxfdp1,&rset,NULL,NULL,NULL);
		if(FD_ISSET(svrfd,&rset)){
			// 服务器socket可读
			if(read(svrfd,recv,1024) <= 0){
				printf("recv failed.");
				exit(1);
			}
			puts(recv);
		}
		if(FD_ISSET(fileno(stdin),&rset)){
			// 标准输入可读
			write(svrfd,line,strlen(line));
		}
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

	// connect 函数会填充套接字对应的tcp四元组，也就是选择一个可用的本地IP地址与一个随机端口（50000-65000）
	// 当然，你可以在调用connect之前先调用bind，指明本地ip和端口，但这种操作并不常见
	if(connect(svrfd,(struct sockaddr *) & svraddr,sizeof(struct sockaddr)) < 0 ){
		printf("connect failed.");
		exit(1);
	}

	write2svr(svrfd);

	return 0;
}
