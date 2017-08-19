#include "net_utils.h"
#include "daemond.h"
#include <stdio.h>
#include <syslog.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/resource.h>
#include <string.h>


void collect_message_log(){
	FILE * fout = popen("tail -f /var/log/messages","r");
	if(fout == NULL){
		syslog(LOG_INFO,"log_agent: popen error");
		exit(1);
	}

	char line[1024];

        while (fgets(line, sizeof(line), fout))
        {
		string out;
		libcurl_post("http://localhost/blog/saveComments.do",line,out,NULL);	            
        }
        
       pclose(fout);	
}

/*
 * ps axu | grep log_agent.app | grep -v grep | awk '{print $2}' | xargs strace -p
 */
int main(int argc,char * argv[]){
	if(sampled_running() > 0){
		exit(0);
	}

	if( sampled() != 0){
		exit(1);	
	}
	
	collect_message_log();
}
