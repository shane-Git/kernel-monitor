#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
int main(void)
{
	FILE *fp =NULL;
	int k =0;
	char str[50];
	char str_odd[50];
	fp = open("/dev/chdev",O_RDWR,S_IRUSR|S_IWUSR);
	if(fp == NULL)
	{
		printf("Open failed.\n");
		return 1;
	}
	while(1)
	{
		strcpy(str_odd,str);
		read(fp,str,30);
		if(strcmp(str_odd,str)!=0)
		{
			printf("%s\n",str);
		}
	}
	return 0;
}
