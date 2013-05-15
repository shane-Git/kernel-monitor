#include<stdio.h>
#include<unistd.h>
#include<sys/mman.h>
#include<sys/stat.h>
#include<fcntl.h>

int main(void)
{
	unsigned char *mmap_base;
	int n,fd,i;
	fd = open("/dev/mem", O_RDWR|O_SYNC);
	if(fd == -1)
	{
		printf("Can't open file!\n");
		return (-1);
	}

	unsigned int LengthOfMap = 0x8000;
	mmap_base = mmap(NULL, LengthOfMap, PROT_READ, MAP_SHARED, fd, 0xb8000);

	if( mmap_base == 0 )
	{
		printf("Can't get the pionter from mem.\n");
		return (-1);
	}
	else
	{
		printf("Already get the poionter,0x%lx\n",mmap_base);
	}

	for(i = 0; i<LengthOfMap; i++)
	{
//		printf("address:0x%lx\tcontent:0x%x\tASCII char:%c\n",mmap_base+i,(unsigned char)*(mmap_base+i),(unsigned char)*(mmap_base+i));
		printf("%c",(unsigned char)*(mmap_base+i));
	}
	close(fd);
	munmap(mmap_base, LengthOfMap);
}
