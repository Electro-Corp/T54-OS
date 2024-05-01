/*
    Header for VGA
*/
#ifndef VGA_H
#define VGA_H

#include "io.h"
#include "string.h"

static int row = 0;

// Terminal
void initTerminal();
void kprintf(char*, ...);
void dkprintf(char* string);

// UTILS
void charAt(char c, int x, int y, unsigned char color);

#endif