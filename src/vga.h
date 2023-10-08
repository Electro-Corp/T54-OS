/*
    Header for VGA
*/
#include "io.h"
#include "string.h"

// Terminal
void initTerminal();
void kprintf(char *string, ...);
void dkprintf(char* string);

// UTILS
void charAt(char c, int x, int y, unsigned char color);