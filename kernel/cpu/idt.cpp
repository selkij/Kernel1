#include <stdint.h>
#include <include/cpu/pic.hpp>
#include <include/lib/panic.hpp>
#include <include/lib/printf.hpp>

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
	panic("Divide by zero exception", 0);
}

__attribute__((interrupt))
void debug_handler(struct interrupt_frame *frame) 
{
    panic("Debug exception", 0);
}

__attribute__((interrupt))
void nmi_handler(struct interrupt_frame *frame) 
{
    panic("NMI exception", 0);
}

__attribute__((interrupt))
void breakpoint_handler(struct interrupt_frame *frame) 
{
    panic("Breakpoint exception", 0);
}

__attribute__((interrupt))
void overflow_handler(struct interrupt_frame *frame) 
{
    panic("Overflow exception", 0);
}

__attribute__((interrupt))
void bound_range_handler(struct interrupt_frame *frame) 
{
    panic("Bound range exceeded exception", 0);
}


__attribute__((interrupt))
void invalid_opcode_handler(struct interrupt_frame *frame) 
{
    panic("Invalid OpCode exception", 0);
}

__attribute__((interrupt))
void device_unavailable_handler(struct interrupt_frame *frame) 
{
    panic("Device Not Available exception", 0);
}

__attribute__((interrupt))
void doublef_handler(struct interrupt_frame *frame, uint64_t error_code) 
{
    panic("Double Fault exception", error_code);
}

__attribute__((interrupt))
void coprocessor_segmentf_handler(struct interrupt_frame *frame) 
{
    panic("Co-processor Segment Fault exception", 0);
}

__attribute__((interrupt))
void invalid_tss_handler(struct interrupt_frame *frame, uint64_t error_code) 
{
    panic("Invalid TSS exception", error_code);
}

__attribute__((interrupt))
void segment_not_present_handler(struct interrupt_frame *frame, uint64_t error_code) 
{
    panic("Segment not present exception", error_code);
}

__attribute__((interrupt))
void stack_segmentf_handler(struct interrupt_frame *frame, uint64_t error_code) 
{
    panic("Stack-segment Fault exception", error_code);
}

__attribute__((interrupt))
void gpf_handler(struct interrupt_frame *frame, uint64_t error_code) 
{
    panic("General Protection Fault exception", error_code);
}

__attribute__((interrupt))
void pagef_handler(struct interrupt_frame *frame, uint64_t error_code) 
{
    panic("Page Fault exception", error_code);
}

__attribute__((interrupt))
void x87_fp_handler(struct interrupt_frame *frame) 
{
    panic("x87 Floating Point exception", 0);
}

__attribute__((interrupt))
void alignment_check_handler(struct interrupt_frame *frame, uint64_t error_code) 
{
    panic("Alignment Check exception", error_code);
}

__attribute__((interrupt))
void machine_check_handler(struct interrupt_frame *frame) 
{
    panic("Machine Check exception", 0);
}

__attribute__((interrupt))
void simd_fp_handler(struct interrupt_frame *frame) 
{
    panic("SIMD floating-point exception", 0);
}

__attribute__((interrupt))
void virtualization_handler(struct interrupt_frame *frame) 
{
    panic("Virtualization Exception", 0);
}

__attribute__((interrupt))
void control_protection_handler(struct interrupt_frame *frame, uint64_t error_code) 
{
    panic("Control Protection exception", error_code);
}

__attribute__((interrupt))
void hyperv_injection_handler(struct interrupt_frame *frame) 
{
    panic("Hypervisor Injection Exception", 0);
}

__attribute__((interrupt))
void vmm_com_handler(struct interrupt_frame *frame, uint64_t error_code) 
{
    panic("VMM Communication exception", error_code);
}

__attribute__((interrupt))
void security_handler(struct interrupt_frame *frame, uint64_t error_code) 
{
    panic("Security exception", error_code);
}

void idt_init() 
{
	idt_set_descriptor(0, (void*)divby0_handler); // Register exceptions
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

    irq_set_mask(0); // Register IRQs
    irq_set_mask(1); 
    irq_set_mask(2);
    irq_set_mask(3);
    irq_set_mask(4);
    irq_set_mask(5);
    irq_set_mask(6);
    irq_set_mask(7);
    irq_set_mask(8);
    irq_set_mask(9);
    irq_set_mask(10);
    irq_set_mask(11);
    irq_set_mask(12);
    irq_set_mask(13);
    irq_set_mask(14);
    irq_set_mask(15);

	asm volatile ("lidt %0" : : "m"(idtr)); // load IDT
	asm volatile ("sti"); // ints enable

    printf("[\u001b[92mINFO\u001b[0m] Initialized IDT\n");
}

