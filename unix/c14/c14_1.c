#include <apue.h>
#include <errno.h>
#include <fcntl.h>

char buf[50000];

int main(int argc, char * argv[]){
    int ntowrite,nwrite;
    char * ptr;

    ntowrite = read(STDIN_FILENO,buf,sizeof(buf));
    fprintf(stderr,"read %d bytes \n",ntowrite);

    set_fl(STDOUT_FILENO,O_NONBLOCK);
    ptr = buf;
    while(ntowrite){

        errno = 0;
        nwrite = write(STDOUT_FILENO,ptr,ntowrite);
        fprintf(stderr,"nwrite = %d,errno = %d\n",ntowrite,errno);

        if(nwrite > 0){
            ptr += nwrite;
            ntowrite -= nwrite;
        }

    }
    clr_fl(STDOUT_FILENO,O_NONBLOCK);

	return 0;
}
