#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/interrupt.h>
#include <asm/io.h>
#include <asm/apic.h>

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
	unsigned long int msrl = 0, msrh = 0;
	unsigned long long int tmp;
	unsigned long int APIC_ID_Register = 0, APIC_Version_Register = 0;
	unsigned long int Interrupt_Command_Regisrer_Low = 0, Interrupt_Command_Regisrer_High = 0;
	asm volatile ("rdmsr":"=a"(msrl),"=d"(msrh):"c"(msr));
	tmp = ((unsigned long long)msrh << 32 |msrl);
	APIC_ID_Register	= native_apic_mem_read(0x20);
	APIC_Version_Register = native_apic_mem_read(0x30);
	Interrupt_Command_Regisrer_Low = native_apic_mem_read(0x300);
	Interrupt_Command_Regisrer_High = native_apic_mem_read(0x310);
	printk(KERN_INFO"Got data from msr:%llx\nLow 32bits:\t %lx\nHigh 32bits:\t %lx\nAPIC_ID_Register:\t%lx\nAPIC_Version_Register:\t%lx\nInterrupt_Command_Regisrer_High:\t %lx\nInterrupt_Command_Regisrer_Low:\t %lx\n",tmp,msrl,msrh,APIC_ID_Register,APIC_Version_Register, Interrupt_Command_Regisrer_High, Interrupt_Command_Regisrer_Low);
//	long int port_adidr;
//	port_addr = (unsigned long)ioremap(0x0000001B,0x8);
//	printk(KERN_INFO"Got data %lx\n",port_addr);
/*
	result = request_irq(1,(irq_handler_t) irq_handler, IRQF_SHARED,"keyboard_stats_irq",(void*)(irq_handler));
	if(result)
	{
		printk(KERN_INFO"Can't get shared interrupt for keyboard\n");
	}
	return result;
	*/
	return 0;
}

void cleanup_module(void)
{
//	free_irq(1, (void *)(irq_handler));
}
