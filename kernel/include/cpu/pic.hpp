#pragma once

#define PIC1		0x20		/* IO base address for master PIC */
#define PIC2		0xA0		/* IO base address for slave PIC */
#define PIC1_COMMAND	PIC1
#define PIC1_DATA	(PIC1+1)
#define PIC2_COMMAND	PIC2
#define PIC2_DATA	(PIC2+1)
#define PIC_EOI		0x20		/* End-of-interrupt command code */
#define PIC_READ_IRR 0x0a    /* OCW3 irq ready next CMD read */
#define PIC_READ_ISR 0x0b    /* OCW3 irq service next CMD read */

void pic_init();
uint16_t pic_get_irr();
uint16_t pic_get_isr();

void irq_set_mask(unsigned char IRQline);
void irq_clear_mask(unsigned char IRQline);

void pic_sendEOI(unsigned char irq);