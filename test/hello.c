#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/interrupt.h>
#include <asm/io.h>


irq_handler_t irq_handler(int irq, void *dev_id, struct pt_regs *regs)
{
	static unsigned char scancode;
	scancode = inb(0x60);
	if((scancode == 0x01) ||(scancode == 0x81) )
	{
		printk(KERN_INFO "You pressed Esc! \n");
	}
	return(irq_handler_t) IRQ_HANDLED;
}

int init_module(void)
{
	int result;
	unsigned int msr = 0x001B;
	unsigned long msrl = 0, msrh = 0, tmp;
	asm volatile ("rdmsr":"=a"(msrl),"=d"(msrh):"c"(msr));
	tmp = ((unsigned long long)msrh << 32 |msrl);
	printk(KERN_INFO"Got data %lx\n",tmp);
//	long int port_addr;
//	port_addr = (unsigned long)ioremap(0x0000001B,0x8);
//	printk(KERN_INFO"Got data %lx\n",port_addr);
	result = request_irq(1,(irq_handler_t) irq_handler, IRQF_SHARED,"keyboard_stats_irq",(void*)(irq_handler));
	if(result)
	{
		printk(KERN_INFO"Can't get shared interrupt for keyboard\n");
	}
	return result;
}

void cleanup_module(void)
{
	free_irq(1, (void *)(irq_handler));
}
