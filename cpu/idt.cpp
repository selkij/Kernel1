#include <stdint.h>
#include "kernel.hpp"

struct idt_entry_t
{
    uint16_t isr_low;      // The lower 16 bits of the ISR's address
    uint16_t kernel_cs;    // The GDT segment selector that the CPU will load into CS before calling the ISR
    uint8_t     ist;          // The IST in the TSS that the CPU will load into RSP; set to zero for now
    uint8_t  attributes;   // Type and attributes; see the IDT page
    uint16_t isr_mid;      // The higher 16 bits of the lower 32 bits of the ISR's address
    uint32_t isr_high;     // The higher 32 bits of the ISR's address
    uint32_t reserved;     // Set to zero
} __attribute__((packed));

struct idtr_t
{
	uint16_t size;
	uint64_t offset;
}__attribute__((packed));

idt_entry_t ivt[256];
idtr_t idtr 
{
	.size = sizeof(idt_entry_t) * 256 - 1,
	.offset = (uint64_t) &ivt[0],
};

void idt_init() 
{
	asm volatile ("sti"); // enable ints
	idt_set_descriptor(0, divby0_handler); // register div by 0 handler
	asm volatile ("lidt %0" : : "m"(idtr)); // load idt
	asm volatile ("sti"); // ints enable
}

void idt_set_descriptor(uint8_t vector, void* isr)
{
    idt_entry_t* descriptor = &ivt[vector];
 
    descriptor->isr_low       = (uint64_t)isr & 0xFFFF;
    descriptor->kernel_cs     = 40; // descriptor entry_num * 8, 64-bit code descriptor is the 5th so 5*8=40
    descriptor->ist           = 0;
    descriptor->attributes    = 0x8E;
    descriptor->isr_mid       = ((uint64_t)isr >> 16) & 0xFFFF;
    descriptor->isr_high      = ((uint64_t)isr >> 32) & 0xFFFFFFFF;
    descriptor->reserved      = 0;
}

__attribute__((interrupt))
void divby0_handler()
{
	print("div by 0 yay");
    while (true)
        asm volatile ("cli; hlt");
}