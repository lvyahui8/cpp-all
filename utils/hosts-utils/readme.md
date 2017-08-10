## make

### lib

安装依赖

```shell
wget https://jaist.dl.sourceforge.net/project/tclap/tclap-1.2.1.tar.gz 
tar zxvf tclap-1.2.1.tar.gz
cd tclap-1.2.1
./configure
make && make install

yum install boost boost-devel -y
```

定位头文件位置

```shell
updatedb
locate tclap | grep "\.h$" | grep CmdLine
```

格式化hosts

```shell
➜  hosts-utils git:(master) ✗ ./hosts_utils.app -f hosts -a format | head                                                
184.28.188.153  		0-act.channel.facebook.com
31.13.95.46     		0-edge-chat.facebook.com
64.233.162.82   		0-focus-opensocial.googleusercontent.com
64.233.162.82   		0-open-opensocial.googleusercontent.com
64.233.162.82   		0-wave-opensocial.googleusercontent.com
64.233.162.82   		0.blogger.gmodules.com
64.233.162.82   		0.client-channel.google.com
```
清理hosts

```shell
➜  hosts-utils git:(master) ✗ ./hosts_utils.app -f new_hosts -a clean
➜  hosts-utils git:(master) ✗ cat new_hosts 
127.0.0.1       		localhost  localhost.localdomain VM_25_177_centos
::1             		localhost localhost.localdomain localhost6 localhost6.localdomain6
```
