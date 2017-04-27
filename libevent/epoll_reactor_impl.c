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
#define SERV_PORT   (8080)

// 对epoll_event的包装，变量地址放在epoll_event.data.ptr中，events放在epoll_event.events中
// status : 1 表示在监听事件中，0表示不在
// last_active : 记录最后一次响应时间，做超时处理
// 每个事件有自己的处理器（call_back）
struct myevent_s {
    int fd;     // cfd listenfd
    int events; // EPOLLIN EPOLLOUT
    void * arg; // 指向字节结构体指针
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
        printf("%s : accept, %d\n",__func__,stderror(errno));
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
            printf("%s: fcntl nonblocking failed , %d\n",__func__,stderror(errno));
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
    
}
void send_data(int fd,int events,void * arg){
    
}


