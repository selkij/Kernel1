#pragma once

#include <stdint.h>
#include <stddef.h>
#include <include/lib/printf.hpp>
#include "pic.hpp"
#include "../drivers/ps2/keyboard.hpp"

extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

void irq_init();
void irq_install_handler(uint8_t num, void (*handler)(struct registers *));
void irq_uninstall_handler(uint8_t num);
void irq_handler(struct registers *r);
