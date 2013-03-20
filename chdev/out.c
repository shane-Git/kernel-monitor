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
	fp = open("chdev",O_RDWR,S_IRUSR|S_IWUSR);
	if(fp == NULL)
	{
		printf("Open failed.\n");
		return 1;
	}
	read(fp,str,30);
	printf("%s\n",str);
	return 0;
}
