#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/tty_driver.h>
#include <linux/tty.h>
#include <asm/uaccess.h>

#define DEVICE_NAME "chdev"
#define BUF_LEN 1024
#define DEV_NO 66
#define CAT_MINORS 90

static int Device_Open = 0;
static char devbuffer[BUF_LEN];
struct semaphore mu;
int i;

static struct tty_driver *cat;

static int device_open(struct inode *inode, struct file *file)
{
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
		printk(KERN_INFO"Encountered Some problems with the read of device%ld\n",length);
		return -EFAULT;
	}
	printk("Once read %ld\n",length);
	return length;
}

static ssize_t device_write(struct file *file,const char *buffer, size_t length, loff_t *offset)
{
//	down_interruptible(&mu);
	for(i=0;i<BUF_LEN;i++)
	{
		devbuffer[i]=0;
	}
	if(copy_from_user(devbuffer,buffer,length))
	{
		printk("Write Function Encountered some error\n");
		return 1;
	}
//	up(&mu);
	printk("Once write %ld\n",length);
	return length;
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
	cat = alloc_tty_driver(CAT_MINORS);
	if(!cat)
	{
		return -ENOMEM;
	}

	static struct tty_operations cat_ops = 
	{
		.open = device_open,
		.close = device_release,
		.write = device_write,
	};

	cat->owner = THIS_MODULE;
	cat->driver_name = "CAT";
	cat->name = "tty_CAT";
//	cat->devfs_name = "FakeCat";
	cat->major = 240;
	cat->type = TTY_DRIVER_TYPE_SERIAL;
	cat->subtype = SERIAL_TYPE_NORMAL;
	cat->flags = TTY_DRIVER_REAL_RAW;
//	cat->init_termios = tty_std_termios;
	cat->init_termios.c_cflag = B9600 | CS8 | CREAD | HUPCL |CLOCAL;
	tty_set_operations(cat,&cat_ops);


//	register_chrdev(DEV_NO, DEVICE_NAME, &fops);
	printk(KERN_INFO "Load chdev device into kernel.\n");
	printk(KERN_INFO "Let's find what is in the struct %d,%d\n",cat->major);
	int retval = 0;
	retval = tty_register_driver(cat);
	if(retval)
	{
		printk(KERN_ERR "Failed to register cat driver\n");
		return retval;
	}
//	sema_init(&mu,1);
	return 0;
}

void cleanup_module(void)
{
	tty_unregister_driver(cat);
	printk("Unload chdev device from kernel.\n");
//	unregister_chrdev(DEV_NO, DEVICE_NAME);
}

MODULE_LICENSE("BSD");
MODULE_AUTHOR("Shane_Wayne<zx0319@gmail.com>");
