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

struct interrupt_frame
{
    uint64_t rip;
    uint64_t cs;
    uint64_t rflags;
    uint64_t rsp;
    uint64_t ss;
};

__attribute__ ((interrupt))
void divby0_handler(struct interrupt_frame *frame)
{
	print("\u001b[31m[CPU Exception]\u001b[0m Divide by zero exception\n");
    for(;;)
        asm volatile ("cli; hlt");
}

__attribute__((interrupt))
void debug_handler(struct interrupt_frame *frame) 
{
    print("\u001b[31m[CPU Exception]\u001b[0m Debug exception\n");
    for(;;)
        asm volatile ("cli; hlt");
}

__attribute__((interrupt))
void nmi_handler(struct interrupt_frame *frame) 
{
    print("\u001b[31m[CPU Exception]\u001b[0m NMI exception\n");
    for(;;)
        asm volatile ("cli; hlt");
}

__attribute__((interrupt))
void breakpoint_handler(struct interrupt_frame *frame) 
{
    print("\u001b[31m[CPU Exception]\u001b[0m Breakpoint exception\n");
    for(;;)
        asm volatile ("cli; hlt");
}

__attribute__((interrupt))
void overflow_handler(struct interrupt_frame *frame) 
{
    print("\u001b[31m[CPU Exception]\u001b[0m Overflow exception\n");
    for(;;)
        asm volatile ("cli; hlt");
}

__attribute__((interrupt))
void bound_range_handler(struct interrupt_frame *frame) 
{
    print("\u001b[31m[CPU Exception]\u001b[0m Bound range exceeded exception\n");
    for(;;)
        asm volatile ("cli; hlt");
}


__attribute__((interrupt))
void invalid_opcode_handler(struct interrupt_frame *frame) 
{
    print("\u001b[31m[CPU Exception]\u001b[0m Invalid OpCode exception\n");
    for(;;)
        asm volatile ("cli; hlt");
}

__attribute__((interrupt))
void device_unavailable_handler(struct interrupt_frame *frame) 
{
    print("\u001b[31m[CPU Exception]\u001b[0m Device Not Available exception\n");
    for(;;)
        asm volatile ("cli; hlt");
}

__attribute__((interrupt))
void doublef_handler(struct interrupt_frame *frame, uint64_t error_code) 
{
    print("\u001b[31m[CPU Exception]\u001b[0m Double Fault exception: " + error_code + '\n');
    for(;;)
        asm volatile ("cli; hlt");
}

__attribute__((interrupt))
void coprocessor_segmentf_handler(struct interrupt_frame *frame) 
{
    print("\u001b[31m[CPU Exception]\u001b[0m Co-processor Segment Fault exception\n");
    for(;;)
        asm volatile ("cli; hlt");
}

__attribute__((interrupt))
void invalid_tss_handler(struct interrupt_frame *frame, uint64_t error_code) 
{
    print("\u001b[31m[CPU Exception]\u001b[0m Invalid TSS exception: " + error_code + '\n');
    for(;;)
        asm volatile ("cli; hlt");
}

__attribute__((interrupt))
void segment_not_present_handler(struct interrupt_frame *frame, uint64_t error_code) 
{
    print("\u001b[31m[CPU Exception]\u001b[0m Segment not present exception: " + error_code + '\n');
    for(;;)
        asm volatile ("cli; hlt");
}

__attribute__((interrupt))
void stack_segmentf_handler(struct interrupt_frame *frame, uint64_t error_code) 
{
    print("\u001b[31m[CPU Exception]\u001b[0m Stack-segment Fault exception: " + error_code + '\n');
    for(;;)
        asm volatile ("cli; hlt");
}

__attribute__((interrupt))
void gpf_handler(struct interrupt_frame *frame, uint64_t error_code) 
{
    print("\u001b[31m[CPU Exception]\u001b[0m General Protection Fault exception: " + error_code + '\n');
    for(;;)
        asm volatile ("cli; hlt");
}

__attribute__((interrupt))
void pagef_handler(struct interrupt_frame *frame, uint64_t error_code) 
{
    print("\u001b[31m[CPU Exception]\u001b[0m Page Fault exception: " + error_code + '\n');
    for(;;)
        asm volatile ("cli; hlt");
}

__attribute__((interrupt))
void x87_fp_handler(struct interrupt_frame *frame) 
{
    print("\u001b[31m[CPU Exception]\u001b[0m x87 Floating Point exception\n");
    for(;;)
        asm volatile ("cli; hlt");
}

__attribute__((interrupt))
void alignment_check_handler(struct interrupt_frame *frame, uint64_t error_code) 
{
    print("\u001b[31m[CPU Exception]\u001b[0m Alignment Check exception: " + error_code + '\n');
    for(;;)
        asm volatile ("cli; hlt");
}

__attribute__((interrupt))
void machine_check_handler(struct interrupt_frame *frame) 
{
    print("\u001b[31m[CPU Exception]\u001b[0m Machine Check exception\n");
    for(;;)
        asm volatile ("cli; hlt");
}

__attribute__((interrupt))
void simd_fp_handler(struct interrupt_frame *frame) 
{
    print("\u001b[31m[CPU Exception]\u001b[0m SIMD floating-point exception\n");
    for(;;)
        asm volatile ("cli; hlt");
}

__attribute__((interrupt))
void virtualization_handler(struct interrupt_frame *frame) 
{
    print("\u001b[31m[CPU Exception]\u001b[0m Virtualization Exception\n");
    for(;;)
        asm volatile ("cli; hlt");
}

__attribute__((interrupt))
void control_protection_handler(struct interrupt_frame *frame, uint64_t error_code) 
{
    print("\u001b[31m[CPU Exception]\u001b[0m Control Protection exception: " + error_code + '\n');
    for(;;)
        asm volatile ("cli; hlt");
}

__attribute__((interrupt))
void hyperv_injection_handler(struct interrupt_frame *frame) 
{
    print("\u001b[31m[CPU Exception]\u001b[0m Hypervisor Injection Exception\n");
    for(;;)
        asm volatile ("cli; hlt");
}

__attribute__((interrupt))
void vmm_com_handler(struct interrupt_frame *frame, uint64_t error_code) 
{
    print("\u001b[31m[CPU Exception]\u001b[0m VMM Communication exception: " + error_code + '\n');
    for(;;)
        asm volatile ("cli; hlt");
}

__attribute__((interrupt))
void security_handler(struct interrupt_frame *frame, uint64_t error_code) 
{
    print("\u001b[31m[CPU Exception]\u001b[0m Security exception: " + error_code + '\n');
    for(;;)
        asm volatile ("cli; hlt");
}

void idt_init() 
{
    print("\u001b[92m[INFO]\u001b[0m Initializing IDT\n");

	idt_set_descriptor(0, (void*)divby0_handler);
    idt_set_descriptor(1, (void*)debug_handler);
    idt_set_descriptor(2, (void*)nmi_handler);
    idt_set_descriptor(3, (void*)breakpoint_handler);
    idt_set_descriptor(4, (void*)overflow_handler);
    idt_set_descriptor(5, (void*)bound_range_handler);
    idt_set_descriptor(6, (void*)invalid_opcode_handler);
    idt_set_descriptor(7, (void*)device_unavailable_handler);
    idt_set_descriptor(8, (void*)doublef_handler);
    idt_set_descriptor(9, (void*)coprocessor_segmentf_handler);
    idt_set_descriptor(10, (void*)invalid_tss_handler);
    idt_set_descriptor(11, (void*)segment_not_present_handler);
    idt_set_descriptor(12, (void*)stack_segmentf_handler);
    idt_set_descriptor(13, (void*)gpf_handler);
    idt_set_descriptor(14, (void*)pagef_handler);
    idt_set_descriptor(16, (void*)x87_fp_handler);
    idt_set_descriptor(17, (void*)alignment_check_handler);
    idt_set_descriptor(18, (void*)machine_check_handler);
    idt_set_descriptor(19, (void*)simd_fp_handler);
    idt_set_descriptor(20, (void*)virtualization_handler);
    idt_set_descriptor(21, (void*)control_protection_handler);
    idt_set_descriptor(28, (void*)hyperv_injection_handler);
    idt_set_descriptor(29, (void*)vmm_com_handler);
    idt_set_descriptor(30, (void*)security_handler);

	asm volatile ("lidt %0" : : "m"(idtr)); // load idt
	asm volatile ("sti"); // ints enable
}

