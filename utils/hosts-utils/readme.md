## make

### lib

wget https://jaist.dl.sourceforge.net/project/tclap/tclap-1.2.1.tar.gz 
tar zxvf tclap-1.2.1.tar.gz
cd tclap-1.2.1
./configure
make && make install

updatedb
locate tclap | grep "\.h$" | grep CmdLine


