#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EVENT_SIZE 10

void (* listeners[EVENT_SIZE])(int);
void small_listener(int e){
	printf("event:%d\n",e);
}

void (* set_listener(int e,void (* listener) (int))) (int){
	void (*old)(int) = listeners[e];
	listeners[e] = listener;
	return old;
}

int main(){
	memset(listeners,NULL,(sizeof listeners[0]) * EVENT_SIZE);
	void (* old_listener) (int) = set_listener(0,small_listener);
	listeners[0](2);
	system("pause");
	return 0;
}

