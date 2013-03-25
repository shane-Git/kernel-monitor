#include <linux/module.h>
#include <linux/init.h>

int init_module(void)
{
	printk(KERN_ERR "Test is actived!\n");
	return 0;
}

void cleanup_module(void)
{
	printk(KERN_ERR "Test is disabled!\n");
}

MODULE_LICENSE("BSD");
MODULE_AUTHOR("Shane_Wayne<zx0319@gmail.com>");
