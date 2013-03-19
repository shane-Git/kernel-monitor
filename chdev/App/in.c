#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
int main(void)
{
	FILE *fp =NULL;
	int k =0;
	char name[10];
	char buffer[40];
	char str[50];
	fp = open("/dev/chdev",O_RDWR,S_IRUSR|S_IWUSR);
	if(fp == NULL)
	{
		printf("Open failed.\n");
		return 1;
	}
	printf("Enter you name:");
	scanf("%s",name);
	while(1)
	{
		printf("Say some thing:");
		scanf("%s",buffer);
		strcpy(str,name);
		strcat(str,":");
		strcat(str,buffer);
		write(fp,str,strlen(str));
	}
	return 0;
}
