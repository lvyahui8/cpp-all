#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void join(const int * const arr,int n,char * buf,char * dm){
	int dmlen = strlen(dm);
	int i,totallen = -1,len,t;
	char * cp;	
	short * lenmap = malloc(sizeof(short) * n);
	for(i = 0 ; i < n;i ++){
		t = arr[i];
		if(0 == t) len = 1;
		else for(len=0;t > 0;len ++,t = t/10);
		totallen += len;
		lenmap[i] = len;
	}	
	totallen += dmlen * (n - 1) + 1;
	cp = buf;
	for(i = 0; i < n && cp != (buf + totallen);i ++){
		if(i == 0){
			sprintf(cp,"%d",arr[i]);
			cp += lenmap[i] ;
		} else {
			sprintf(cp,"%c%d",*dm,arr[i]);
			cp += (lenmap[i] + dmlen);
		}
	}	
	*++cp='\0';
	free(lenmap);
}

void swap(int * a , int * b){
	*a = *a + *b;
	*b = *a - *b;
	*a = *a - *b;
}
char buf[1024];

void ksort(int arr[],int l,int r){
	if(r - l < 1) return;
	int start = l,end = r + 1;
	while(start < end){
		while(start < r && arr[++start] < arr[l]);
		while(end > l && arr[--end] > arr[l]);
		if(start < end){
			swap(arr + start,arr + end);
		}
	}
	swap(arr + l,arr + end);
	ksort(arr, l , end);
	ksort(arr, start + 1, r);
	return;
}

int main(){
	int arr[] = {5000,4,30,2,1,9,8,7,6,0}; 
	char buf[1024];
	join(arr,sizeof(arr) / sizeof(int),buf,",");
	printf("%s\n",buf);
	ksort(arr,0,sizeof(arr) / sizeof(int) - 1);
	join(arr,sizeof(arr) / sizeof(int),buf,",");
	printf("%s\n",buf);
	return 0;
}
