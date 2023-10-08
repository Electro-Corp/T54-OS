/*
    Kernel Entrypoint
*/
#include "vga.h"

int kmain(){
    // Init display
    initTerminal();
    kprintf("[Kernel] T54 Display Initilized");
    // Init fs
    initFS();
    kprintf("[Kernel] Launching /bin/init");
    asm("hlt");
}   