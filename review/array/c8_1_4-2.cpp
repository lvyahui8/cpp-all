// ָ��Ч�ʣ���������
#define SIZE 50
int x[SIZE];
int y[SIZE];
int i;
int *p1,*p2;

void try1(){
	for(p1 = x, p2 = y; p1 -x < SIZE;){
		* p1++ = * p2++;
	}
}