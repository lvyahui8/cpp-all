#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int a ;
	char b;
	//const char (*p_emails) [20]; // ���Ƕ�����һ����ָ�룬ָ��20��Ԫ�ص�һ������
	const char * p_emails[5]; // ���Ƕ�������ָ�����飬ÿ��Ԫ�ؽ�ָ��һ��һά����ĵ�һ��Ԫ��
} sim_t;

int main(){
	sim_t sim = {
		10,
		'b',
		{"lvyahui8@gmail.com","lvyahui8@126.com","tumbler0816@qq.com"}
	};
	sim_t * p_sim = &sim;
	p_sim->a = 11;
	p_sim->b = 'a';

	printf("sim.a = %d\n",sim.a);
	printf("sim.b = %c\n",sim.b);

	for (int i = 0 ; i < sizeof(p_sim->p_emails) / sizeof(p_sim->p_emails[0]); i ++)
	{
		if(NULL != p_sim->p_emails [i]){
			printf("%s\n",p_sim->p_emails [i]);
		}		
	}
	
	for (const char * p_str = p_sim->p_emails[0] ; p_str < (p_sim->p_emails + 1); p_str ++)
	{
		if(NULL != p_str){
			puts(p_str);
		}
	}
	system("pause");
	return 0;
}