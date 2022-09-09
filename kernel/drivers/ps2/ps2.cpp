#include <include/drivers/ps2/ps2.hpp>
#include <include/cpu/cpu.hpp>
#include <include/lib/printf.hpp>


void ps2_enable() 
{
	while(inb(PS2_STATUS) & (1 << 1)) asm ("pause"); // Enabling PS/2 ports
	outb(PS2_COMMAND, 0xae);
    io_wait();
    
	while(inb(PS2_STATUS) & (1 << 1)) asm ("pause");
	outb(PS2_COMMAND, 0xa8);
    io_wait();
}

void ps2_disable() 
{
    while(inb(PS2_STATUS) & (1 << 1)) asm ("pause"); // Disabling PS/2 ports
    outb(PS2_COMMAND, 0xad);
    io_wait();

    while(inb(PS2_STATUS) & (1 << 1)) asm ("pause");
    outb(PS2_COMMAND, 0xa7);
    io_wait();
}

void ps2_flush_buffer() 
{
    while(inb(PS2_STATUS)& (1 << 0)) 
    {
        inb(PS2_DATA);
    }
}

void ps2_init() 
{
    ps2_flush_buffer();

    while(inb(PS2_STATUS)& (1 << 0)) asm volatile("pause");

    outb(PS2_COMMAND, 0xaa);
    io_wait();

    while(inb(PS2_STATUS)& (0 << 0)) asm volatile("pause");
    
    uint8_t result = inb(PS2_DATA);

    if(result == 0x55) 
    {
        printf("[\u001b[92mINFO\u001b[0m] Initialized PS2 controller\n");
        ps2_enable();
    } 

    if(result == 0xfc)
    {
        printf("\u001b[91m[ERROR]\u001b[0m Failed Initializing PS2 controller, no keyboard will be available\n");
    }
}

