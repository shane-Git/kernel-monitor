#include <linux/module.h>
#include <linux/init.h>
#include <asm/uaccess.h>
#include <linux/console.h>

#define BUF_LEN 128

char devbuffer[BUF_LEN];

static ssize_t device_write(struct file *file, const char *buffer, size_t length, loff_t *offset)
{
	int retval, i;
	for(i = 0; i < BUF_LEN; i++)
	{
		devbuffer[i] = 0;
	}
	if(retval = copy_from_user(devbuffer, buffer, length))
	{
		printk(KERN_ERR "Encounted some error with the write\n");
		return retval;
	}
	printk(KERN_INFO "Once Write %ld", length);
	return length;
}

static struct console ram_console =
{
	.name = "RamConsole",
//	.write = device_write,
	.flags = CON_PRINTBUFFER | CON_ENABLED,
	.index = -1,
};

int init_module(void)
{
	register_console(&ram_console);
//	console_verbose();
	printk(KERN_INFO "The RAM Console is actived!\n");
	return 0;
}

void cleanup_module(void)
{
	unregister_console(&ram_console);
	printk(KERN_INFO "The RAM Console is disabled!\n");
}

MODULE_LICENSE("BSD");
MODULE_AUTHOR("Shane_Wayne<zx0319@gmail.com>");
