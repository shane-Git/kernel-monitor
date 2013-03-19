#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <asm/uaccess.h>

#define DEVICE_NAME "chdev"
#define BUF_LEN 1024
#define DEV_NO 66
static int Device_Open = 0;
static char devbuffer[BUF_LEN];
struct semaphore mu;
int i;

static int device_open(struct inode *inode, struct file *file)
{
	sema_init(&mu,1);
	Device_Open++;
	return 0;
}

static int device_release(struct inode *inode, struct file *file)
{
	Device_Open--;
	return 0;
}

static ssize_t device_read(struct file *filp,char *buffer,size_t length,loff_t *offset)
{
	if(copy_to_user(buffer,devbuffer,length))
	{
		return 1;
	}
//	printk("Once read %d",length);
	return 0;
}

static ssize_t device_write(struct file *file,const char *buffer, size_t length, loff_t *offset)
{
	down_interruptible(&mu);
	for(i=0;i<BUF_LEN;i++)
	{
		devbuffer[i]=0;
	}
	if(copy_from_user(devbuffer,buffer,length))
	{
		return 1;
	}
	up(&mu);
	printk("Once write %d",length);
	return 0;
} 

static struct file_operations fops = 
{
	.read = device_read,
	.write = device_write,
	.open = device_open,
	.release = device_release
};

int init_module(void)
{
	register_chrdev(DEV_NO, DEVICE_NAME, &fops);
	printk("Load chdev device into kernel.\n");
	return 0;
}

void cleanup_module(void)
{
	printk("Unload chdev device from kernel.\n");
	unregister_chrdev(DEV_NO, DEVICE_NAME);
}

MODULE_LICENSE("BSD");
MODULE_AUTHOR("Shane_Wayne<zx0319@gmail.com>");
