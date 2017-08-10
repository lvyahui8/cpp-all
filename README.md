# cpp-all

@(测试代码)[c|c++]

---------

## Make

### lib

安装依赖

tclap
``` bash
wget https://jaist.dl.sourceforge.net/project/tclap/tclap-1.2.1.tar.gz 
tar zxvf tclap-1.2.1.tar.gz
cd tclap-1.2.1
./configure
make && make install
``` 
boost
``` bash
yum install boost boost-devel -y
```
libevent
``` bash
wget https://github.com/libevent/libevent/releases/download/release-2.1.8-stable/libevent-2.1.8-stable.tar.gz
tar zxvf libevent-2.1.8-stable.tar.gz
cd libevent-2.1.8-stable
./configure
make && make install
```
apue3
``` bash
cd /root/soft/
yum install libbsd-devel -y
wget http://www.apuebook.com/src.3e.tar.gz
tar zxvf src.3e.tar.gz && cd apue.3e && make
cp /root/soft/apue.3e/lib/*.o /root/soft/apue.3e/lib/*.a /root/work/cpp-all/unix/lib
```
