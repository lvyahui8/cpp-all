## unix 5 种不同的IO模型

- 阻塞式IO模型
- 非阻塞式IO模型(NIO)
- I/O复用模型
- 信号/事件驱动式I/O模型 
- 异步I/O模型 

默认的阻塞式IO编程是最常用的IO编程模型

非阻塞式IO模型是指在原本应该阻塞的IO操作时，直接返回一个错误，不阻塞

IO复用模型最常用的函数是select

信号驱动式IO编程模型最常用的函数式epoll

异步IO模型将IO操作交给内核处理，并要求内核处理完成之后回调通知应用程序

