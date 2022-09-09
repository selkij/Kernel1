#pragma once

#include <stddef.h>

extern void* memset(void* dest, int val, size_t len);
extern void* memmove(void* dest, const void* src, size_t len);
extern int memcmp(const void* dest, const void* src, size_t len);
extern void* memcpy(void *dest, const void *src, size_t len);