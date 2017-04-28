#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <time.h>

#define MAX_EVENTS  (1024)  // 此值决定了此程序（进程）能处理的并发连接数
#define BUFLEN      (128)
#define SERV_PORT   (7077)

// 对epoll_event的包装，变量地址放在epoll_event.data.ptr中，events放在epoll_event.events中
// status : 1 表示在监听事件中，0表示不在
// last_active : 记录最后一次响应时间，做超时处理
// 每个事件有自己的处理器（call_back）
struct myevent_s {
    int fd;     // cfd listenfd
    int events; // EPOLLIN EPOLLOUT
    void * arg; // 指向结构体本身的指针，存储结构体本身的地址
    void (*call_back)(int fd,int events,void * arg);
    int status;
    char buf[BUFLEN];
    int len;
    long last_active;
};

int g_efd;      // epoll_create 返回的句柄，epfd

struct myevent_s event_fd;
struct myevent_s g_events[MAX_EVENTS];

void recv_data(int fd,int events,void * arg);
void send_data(int fd,int events,void * arg);


// 事件相关操作

void event_init(struct myevent_s * ev,int fd,void (*call_back)(int,int,void*),void * arg){
    ev->fd = fd;
    ev->call_back = call_back;
    ev->events = 0;
    ev->arg = arg;
    ev->status = 0;
    ev->last_active = time(NULL);
}

void event_add(int efd,int events,struct myevent_s * ev){
    struct epoll_event epv = {0,{0}};
    int op;
    epv.data.ptr = ev;
    epv.events = ev->events  = events;
    
    if(ev->status == 1){
        // 在监听中 , 更新时间处理即可
        op = EPOLL_CTL_MOD;
    } else {
        op = EPOLL_CTL_ADD;
        ev->status = 1;
    }
    
    if(epoll_ctl(efd,op,ev->fd,& epv) < 0){
        printf("event add failed [fd=%d], events[%d]\n",ev->fd,events);
    } else {
        printf("event add ok [fd=%d], op=%d, events[%d]\n",ev->fd,op,events);
    }
}

void event_del(int efd,struct myevent_s * ev){
    struct epoll_event epv = {0,{0}};
    
    if(ev->status != 1){
        return ;
    }
    
    epv.data.ptr = ev;
    ev->status = 0;
    epoll_ctl(efd,EPOLL_CTL_DEL,ev->fd, &epv);
    return ;
}

// 连接相关
void accept_conn(int lfd,int events,void * arg){
    struct sockaddr_in cin;
    socklen_t len = sizeof(cin);
    int cfd;
    int i;
    
    if ((cfd = accept(lfd,(struct sockaddr*) & cin, & len)) == -1){
        if(errno != EAGAIN && errno != EINTR){
            // 暂时不做错误处理
        }
        printf("%s : accept, %s\n",__func__,strerror(errno));
        return;
    }
    
    do {
        // 每次寻找一个空闲的事件句柄，以便分配给新来的用户
        for(i = 0 ; i < MAX_EVENTS; i++){
            if(g_events[i].status == 0){
                break;
            }
        }
        
        if(i == MAX_EVENTS){
            printf("%s: max connect limit[%d]\n",__func__,MAX_EVENTS);
            break;
        }
        
        int flag = 0;
        
        if((flag = fcntl(cfd,F_SETFL,O_NONBLOCK)) < 0 ){
            printf("%s: fcntl nonblocking failed , %s\n",__func__,strerror(errno));
            break;
        }
        
        // 连接可以建立，对新来的用户添加事件监听
        event_init(&g_events[i],cfd,recv_data,&g_events[i]);
        event_add(g_efd,EPOLLIN,&g_events[i]);
    } while(0); // 只是限定作用域
    
    printf("new connect [%s:%d][time:%ld],pos[%d]\n",inet_ntoa(cin.sin_addr),ntohs(cin.sin_port),g_events[i].last_active,i);
    
}

// 收发数据
void recv_data(int fd,int events,void * arg){
    struct myevent_s * ev  = ( struct myevent_s * ) arg;
    int len;
    len = recv(fd,ev->buf,sizeof(ev->buf),0);
    
    event_del(g_efd,ev);
    if(len > 0 ){
        ev->len = len;
        ev->buf[len] = '\0';
        printf("C[%d]:%s\n",fd,ev->buf);
        // 响应数据已就绪，转换为发送时间
        event_init(ev,fd,send_data,ev);
        event_add(g_efd,EPOLLOUT,ev);
    } else if(len == 0 ){
        close(ev->fd);
        printf("[fd=%d] pos[%d],closed\n",fd,(int)(ev - g_events));
    } else {
        close(ev->fd);
        printf("recv[fd=%d error[%d]:%s\n",fd,errno,strerror(errno));
    }
}

void send_data(int fd,int events,void * arg){
    struct myevent_s * ev = (struct myevent_s *) arg;
    int len;
    len = send(fd,ev->buf,ev->len,0);
    event_del(g_efd,ev);
    if(len >  0){
        printf("send[fd=%d],[%d]%s\n",fd,len,ev->buf);
        // 发送完毕，转为监听接收
        event_init(ev,fd,recv_data,ev);
        event_add(g_efd,EPOLLIN,ev);
    } else {
        close(ev->fd);
        printf("send[fd=%d] error %s \n",fd,strerror(errno));
    }
}

void init_listen_socket(int efd,short port){
    int lfd = socket(AF_INET,SOCK_STREAM,0);
    fcntl(lfd,F_SETFL,O_NONBLOCK);
    event_init(&event_fd,lfd,accept_conn,&event_fd);
    event_add(efd,EPOLLIN,&event_fd);
    
    struct sockaddr_in sin;
    memset(&sin,0,sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(port);
    
    bind(lfd,(struct sockaddr *) & sin,sizeof(sin));
    
    listen(lfd,20);
   
}

int main(int argc,char * argv[]){
    unsigned short port = SERV_PORT;
    if(argc == 2){
        port = atoi(argv[1]);
    }
    
    g_efd = epoll_create(MAX_EVENTS + 1);
    
    if(g_efd <= 0){
        perror("craete");
        exit(-1);
    }
    
    init_listen_socket(g_efd,port);
    
    struct epoll_event(events[MAX_EVENTS + 1]);
    
    printf("server running:port[%d]\n",port);
    int checkpos = 0 , i;
    while(1){
        // 超时，当每次测试100个连接，不测试listenfd(event_fd)，当客户端60秒内没有与服务器通信，断开连接
        long now = time(NULL);
        for(i = 0 ;i < 100; i++, checkpos = (checkpos + 1 ) % MAX_EVENTS){
            if(g_events[checkpos].status != 1){
                // 没监听事件，已经断开的链接
                continue;
            }
            
            long duration = now - g_events[checkpos].last_active;
            
            if(duration >= 60){
                close(g_events[checkpos].fd);
                printf("[fd=%d] timeout\n",g_events[checkpos].fd);
                event_del(g_efd,&g_events[checkpos]);
            }
        }
        
        // 等待事件发生
        int nfd = epoll_wait(g_efd,events,MAX_EVENTS + 1,1000);
        if(nfd < 0){
            printf("epoll_wait error,exit\n");
            break;
        }
        
        for(i = 0;i < nfd; i ++){
            struct myevent_s * ev = (struct myevent_s *) events[i].data.ptr;
            if((events[i].events & EPOLLIN ) && (ev->events & EPOLLIN)){
                ev->call_back(ev->fd,events[i].events,ev->arg);
            }
            
            if((events[i].events & EPOLLOUT) && (ev->events & EPOLLOUT)){
                ev->call_back(ev->fd,events[i].events,ev->arg);
            }
        }
    }
    return 0;
}

