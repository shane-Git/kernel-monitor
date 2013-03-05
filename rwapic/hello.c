#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/interrupt.h>
#include <asm/io.h>
#include <asm/apic.h>

irq_handler_t irq_handler(int irq, void *dev_id, struct pt_regs *regs)
{
	printk(KERN_INFO "Have a Interrupt \n");
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
	result = request_irq(2,(irq_handler_t) irq_handler, IRQF_DISABLED,"IPI Handler", NULL);
	if(result)
	{
		printk(KERN_INFO"Can't get shared interrupt for keyboard\n");
	}
	Interrupt_Command_Regisrer_High = 0x00;
	Interrupt_Command_Regisrer_Low = 0x32;
	native_apic_mem_write(0x310, Interrupt_Command_Regisrer_High);
	native_apic_mem_write(0x300, Interrupt_Command_Regisrer_Low);
	return result;
}

void cleanup_module(void)
{
	free_irq(2, NULL);
}
