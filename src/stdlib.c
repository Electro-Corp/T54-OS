#include "stdlib.h"

int memcmp(const void* aptr, const void* bptr, int size) {
	const unsigned char* a = (const unsigned char*) aptr;
	const unsigned char* b = (const unsigned char*) bptr;
	for (int i = 0; i < size; i++) {
		if (a[i] < b[i]){
			return -1;
        }
		else if (b[i] < a[i]){
			return 1;
        }
    }
	return 0;
}

void* memcpy(void* restrict dstptr, const void* restrict srcptr, int size) {
	return memcpyBounded(dstptr, srcptr, 0, size);
}


void* memcpyBounded(void* restrict dstptr, const void* restrict srcptr, int start, int size){
    unsigned char* dst = (unsigned char*) dstptr;
	const unsigned char* src = (const unsigned char*) srcptr;
	for (int i = start; i < start + size; i++)
		dst[i] = src[i];
	return dstptr;
}

void reverse(char str[], int length)
{
    int start = 0;
    int end = length - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        end--;
        start++;
    }
}

char* itoa(int num, int base, char* str){
    int i = 0;
    int neg = 0;
    if(num == 0){
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }

    if(num < 0 && base == 10){
        neg = 1;
        num *= -1;
    }

    while(num != 0){
        int rem = num % base;
        str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
        num = num / base;
    }

    if(neg){
        str[i++] = '-';
    }

    str[i] = '\0';

    reverse(str, i);

    return str;
}