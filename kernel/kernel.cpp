#include <stdint.h>
#include <stddef.h>
#include <limine.h>
#include <include/lib/printf.hpp>
#include <include/cpu/idt.hpp>
#include <include/cpu/pic.hpp>
#include <include/drivers/ps2/ps2.hpp>

volatile struct limine_terminal_request __term = {
    .id = LIMINE_TERMINAL_REQUEST,
    .revision = 0
};

static void done(void) {
    for (;;) {
        asm volatile("hlt");
    }
}

extern "C" void _start(void) {
    if (__term.response == NULL
     || __term.response->terminal_count < 1) {
        done();
    }

    idt_init();
    pic_init();
    ps2_init();

    printf("Hello World !\n");
    printf("setsef\n");

    done();
}