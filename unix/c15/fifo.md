## 命名管道
命名管道与管道不同，命名管道以文件的形式表示，可以用于非同族进程间的通信。
同时命名管道为非线性连接，可以借助命名管道实现很复杂的输入输出重定向
FIFO文件在磁盘上没有数据块，仅用来标识内核中的一条通道，这与通过unix domain socket进行ipc通信类似。
fifo文件和socket文件都只是用来标识特殊通道，并不占用磁盘数据块

参考
linux系统编程之管道（三）：命名管道FIFO和mkfifo函数
http://blog.csdn.net/jnu_simba/article/details/8953960

管道和fifo都是system v标准的ipc方法，目前使用的比较少


## 命名管道示例

命名管道可以用代码函数创建，也可以用命名创建

```bash
➜  /tmp mkfifo tmpfifo
➜  /tmp ll
prw-r--r-- 1 root root    0 Aug 30 23:18 tmpfifo

➜  /tmp tail -f tmpfifo > /tmp/tmptail &
➜  /tmp cat /etc/keepalived/keepalived.conf | tee tmpfifo | grep script
➜  /tmp cat /tmp/tmptail 
    virtual_ipaddress {
        10.198.6.190
    }
```

