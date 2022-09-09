#include <stdint.h>
#include <include/cpu/pic.hpp>
#include <include/cpu/cpu.hpp>
#include <include/lib/printf.hpp>

void pic_init() 
{
    unsigned char a1, a2;
 
	a1 = inb(PIC1_DATA); // save masks
	a2 = inb(PIC2_DATA);

    outb(PIC1, 0x11); // Initialise command
    io_wait();
    outb(PIC2, 0x11);
    io_wait();
    outb(PIC1_DATA, 0x20); // Master PIC vector offset
    io_wait();
    outb(PIC2_DATA, 0x28); // Slave PIC vector offset
    io_wait();
    outb(PIC1_DATA, 0x04); // Tell Master PIC that there is a slave PIC at IRQ2
    io_wait();
    outb(PIC2_DATA, 0x02); // Tell Slave PIC its cascade identity
    io_wait();
    outb(PIC1_DATA, 0x01);
    io_wait();
    outb(PIC2_DATA, 0x01);
    io_wait();

    outb(PIC1_DATA, a1); // Restore masks
    outb(PIC2_DATA, a2);

    printf("[\u001b[92mINFO\u001b[0m] Initialized PIC\n");
}

void pic_disable()
{
    outb(0xA1, 0xFF);
    outb(0x21, 0xFF);
}

// TODO: Handle IRQs and ISRs
// TODO: Handling Spurious IRQs

uint16_t __pic_get_irq_reg(int ocw3)
{
    /* OCW3 to PIC CMD to get the register values.  PIC2 is chained, and
     * represents IRQs 8-15.  PIC1 is IRQs 0-7, with 2 being the chain */
    outb(PIC1_COMMAND, ocw3);
    outb(PIC2_COMMAND, ocw3);
    return (inb(PIC2_COMMAND) << 8) | inb(PIC1_COMMAND);
}
 
/* Returns the combined value of the cascaded PICs irq request register */
uint16_t pic_get_irr()
{
    return __pic_get_irq_reg(PIC_READ_IRR);
}
 
/* Returns the combined value of the cascaded PICs in-service register */
uint16_t pic_get_isr()
{
    return __pic_get_irq_reg(PIC_READ_ISR);
}

void irq_set_mask(unsigned char IRQline) {
    uint16_t port;
    uint8_t value;
 
    if(IRQline < 8) {
        port = PIC1_DATA;
    } else {
        port = PIC2_DATA;
        IRQline -= 8;
    }
    value = inb(port) | (1 << IRQline);
    outb(port, value);        
}
 
void irq_clear_mask(unsigned char IRQline) {
    uint16_t port;
    uint8_t value;
 
    if(IRQline < 8) {
        port = PIC1_DATA;
    } else {
        port = PIC2_DATA;
        IRQline -= 8;
    }
    value = inb(port) & ~(1 << IRQline);
    outb(port, value);        
}

void pic_sendEOI(unsigned char irq) 
{
    if(irq >= 8)
		outb(PIC2_COMMAND,PIC_EOI);
 
	outb(PIC1_COMMAND,PIC_EOI);
}