/*
    Basic debugging terminal for T54
    This will be replaced with an executable
    version of bash at some point

    this is really only for debugging the way processes
    launch
*/
#include "io.h"
#include "vga.h"

// Keyboard map
unsigned char keyboard_map[128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',     /* 9 */
  '9', '0', '-', '=', '\b',     /* Backspace */
  '\t',                 /* Tab */
  'q', 'w', 'e', 'r',   /* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', /* Enter key */
    0,                  /* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',     /* 39 */
 '\'', '`',   0,                /* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',                    /* 49 */
  'm', ',', '.', '/',   0,                              /* Right shift */
  '*',
    0,  /* Alt */
  ' ',  /* Space bar */
    0,  /* Caps lock */
    0,  /* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,  /* < ... F10 */
    0,  /* 69 - Num lock*/
    0,  /* Scroll Lock */
    0,  /* Home key */
    '~',  /* Up Arrow */
    0,  /* Page Up */
  '-',
    0,  /* Left Arrow */
    0,
    0,  /* Right Arrow */
  '+',
    0,  /* 79 - End key*/
    '|',  /* Down Arrow */
    0,  /* Page Down */
    0,  /* Insert Key */
    0,  /* Delete Key */
    0,   0,   0,
    0,  /* F11 Key */
    0,  /* F12 Key */
    0,  /* All other keys are undefined */
};

void termInit(){
    // Enable keyboard interrupt
    unsigned char curmask_master = inb(0x21);
    outb(0x21, curmask_master & 0xFD);
    kprintf("==================================");
    kprintf("        T54 DEBUG TERMINAL        ");
    kprintf("==================================");
    kprintf("Used for debugging purposes and launching programs.");
    kprintf("Commands:");
    kprintf("dir -- Lists all directories and files");
    kprintf("launch [file] -- tries to luanch the specified file");
    kprintf(" ");
}
char buffer[2048];
int b = 0;
char* text = "T54> ";
void termLoop(){
    char final[5048] = {0};
    char keycode = keyboard_map[inb(0x60)];
    if(keycode){
        buffer[b++] = keycode;
        strcat(final, text);
        strcat(final, buffer);
        strcat(final, '\r');
        kprintf(final);
    }

    int status = inb(0x64);
    while((status >> 0) & 1 != 1){

    }
}