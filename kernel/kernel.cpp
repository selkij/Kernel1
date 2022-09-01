#include <stdint.h>
#include <stddef.h>
#include <limine.h>
#include "../cpu/idt.hpp"

// The Limine requests can be placed anywhere, but it is important that
// the compiler does not optimise them away, so, usually, they should
// be made volatile or equivalent.

static volatile struct limine_terminal_request terminal_request = {
    .id = LIMINE_TERMINAL_REQUEST,
    .revision = 0
};

static void done(void) {
    for (;;) {
        __asm__("hlt");
    }
}

size_t strlen(const char *str)
{
    size_t length = 0;
    while (*str++)
        length++;
    return length;
}

void print(const char *str)
{
    auto term = terminal_request.response->terminals[0];
    terminal_request.response->write(term, str, strlen(str));
}

// The following will be our kernel's entry point.
extern "C" void _start(void) {
    // Ensure we got a terminal
    if (terminal_request.response == NULL
     || terminal_request.response->terminal_count < 1) {
        done();
    }

    idt_init();
    volatile int div = 0/0;

    print("Hello World\n");
    print("This is Kernel1 made in C++!");
    

    // We're done, just hang...
    done();
}