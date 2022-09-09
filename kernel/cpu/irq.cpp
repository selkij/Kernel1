#include <include/cpu/irq.hpp>

void* irq_handler_table[16] = { };

void irq_init()
{
    irq_install_handler(1, &keyboard_handler);
	// irq_install_handler(12, &mouse_handler);
	
    printf("[\u001b[92mINFO\u001b[0m] Initialized IRQs\n");
}

void irq_install_handler(uint8_t num, void (*handler)(struct registers*))
{
    irq_handler_table[num] = handler;
}

void irq_uninstall_handler(uint8_t num)
{
    irq_handler_table[num] = 0;
}
void irq_handler(struct registers* r)
{
    void (*handler)(struct registers* r);
    handler = irq_handler_table[r->int_no - 32];

    if(handler != NULL)
    {
        handler(r);
    }
    
    // Sends an EOI (End of Interrupt) to the PIC
    pic_sendEOI(r->int_no - 32);
}