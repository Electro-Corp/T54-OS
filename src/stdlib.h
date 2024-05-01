/*
    STDLIB
*/
#ifndef STDLIB_H
#define STDLIB_H
#define NULL ((void *)0)

void* memcpyBounded(void* restrict dstptr, const void* restrict srcptr, int start, int size);

int memcmp(const void* aptr, const void* bptr, int size);

void* memcpy(void* restrict dstptr, const void* restrict srcptr, int size);

char* itoa(int num, int base, char* str);
#endif