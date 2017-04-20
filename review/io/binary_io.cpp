#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SAVE_SIZE 100
#define NAME_SIZE 16
typedef struct {
	int id ;
	char name[NAME_SIZE];
	char sex;
} user;

int main(int argc, char * argv[]){
	char * file = "F:\\user.data";
	FILE * fp = fopen(file,"ab+");

	if(fp == NULL){
		perror(file);
		exit(EXIT_FAILURE);
	}
	int n = SAVE_SIZE;
	user save_users[SAVE_SIZE];
	for (int i = 0 ; i < n ; i++)
	{

		save_users[i].id = i;
		sprintf(save_users[i].name,"lvyahui_%03d",i);
		//save_users[i].name = strcat("lvyahui_",& ((char) (i + '0'))); // �Ƿ��� ��& ȡ��ַʱ����ֵ�����Ǳ��ʽ��������Ϊ��λ�����
		save_users[i].sex = i % 2 == 1 ? 'W' : 'M';
	}
	// ��ס��ʼλ��
	fpos_t start;
	fgetpos(fp,& start); 
	fwrite(save_users,sizeof user,n,fp);
	// ˢ�»��浽�ļ�
	fflush(fp);
	// ���ö�дָ�����ļ�������ʼλ�ã��ļ�ͷ��
	// rewind(fp);
	//fseek(fp,0,SEEK_SET);
	// �ص���������
	fsetpos(fp,& start);
	user read_users[SAVE_SIZE];
	fread(read_users,sizeof user,n,fp);
	for(int j = 0; j < n; j++){
		printf("id:%d name:%s sex:%c\n",
			read_users[j].id,read_users[j].name,read_users[j].sex);
	}

	if(fp != NULL){
		fclose(fp);
	}

	system("pause");
	return EXIT_SUCCESS;
}