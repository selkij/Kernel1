#pragma once
#include <stdint.h>

void keyboard_handler(struct registers * r);
void keyboard_handler(struct registers * r);
int getch();
int getstr(char * buffer);
int getline(char * buffer);