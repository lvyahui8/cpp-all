#include <stdio.h>
#include <stdlib.h>


int main(int argc, char * argv[]){
	int a ,b;
	scanf("a=%d;b=%d",&a,&b);
	printf("a:%d;b:%d\n",a,b);

	char * hosts_file = "E:\\hosts";
	char * out_hosts_file = "F:\\hosts";
	FILE * hosts_input = fopen(hosts_file,"r");
	
	if(hosts_input == NULL){
		perror(hosts_file);
		exit(EXIT_FAILURE);
	}
	FILE * hosts_output = fopen(out_hosts_file,"w+");
	if(hosts_output == NULL){
		perror(out_hosts_file);
		exit(EXIT_FAILURE);
	}
	int ips[4];
	char domain[256];
	int nfields = 0;
	while((nfields = fscanf(hosts_input,"%d.%d.%d.%d %s",ips,ips+1,ips+2,ips+3,domain)) != EOF){
		if(nfields != 5){
			continue;
		}
		fprintf(hosts_output,"%d.%d.%d.%d %s",*ips,ips[1],ips[2],ips[3],domain);
	}
	if(hosts_input != NULL){
		fclose(hosts_input);
	}
	if(hosts_output != NULL){
		fclose(hosts_output);
	}
	system("pause");
	return EXIT_SUCCESS;
}