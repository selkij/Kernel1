#pragma once

#include <stdint.h>
#include <include/cpu/cpu.hpp>
#include <include/lib/memory.hpp>

#define PS2_DATA 0x60
#define PS2_STATUS 0x64
#define PS2_COMMAND 0x64
#define PS2_READ_CONFIG 0x20
#define PS2_WRITE_CONFIG 0x60
#define PS2_READ_CONTROLLER_OUTPUT 0xD0
#define PS2_WRITE_CONTROLLER_OUTPUT 0xD1

void ps2_enable();
void ps2_disable();
void ps2_flush_buffer();
void ps2_init();