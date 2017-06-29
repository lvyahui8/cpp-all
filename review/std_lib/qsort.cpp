#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 50

typedef struct 
{
	char key[10];
	int other_data;
} Record;

int r_compare(const void * a, const void * b){
	return strcmp(((Record *) a)->key,((Record *) b)->key);
}
int main(){

	Record arr[SIZE];
	for (int i =0 ;i < SIZE; i ++)
	{
		sprintf(arr[i].key,"%02d",SIZE - i);
		arr[i].other_data = i + 1;
	}
	qsort(arr,SIZE,sizeof Record,r_compare);
	for (int i =0 ;i  < SIZE ;i ++)
	{
		printf("%s : %02d\n",arr[i].key,arr[i].other_data);
	}

	Record key , * res;
	strcpy(key.key,"05");
	res = (Record *) bsearch(&key,arr,SIZE,sizeof Record,r_compare);
	printf("res %02d\n",res->other_data);
	system("pause");
	return 0;
}