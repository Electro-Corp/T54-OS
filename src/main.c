/*
    Kernel Entrypoint
*/
#include "vga.h"

int kmain(){
    // Init display
    initTerminal();
    kprintf("T54 Display Initilized");
    // Init fs
    initFS();
}   