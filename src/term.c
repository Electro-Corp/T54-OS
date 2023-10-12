/*
    Basic debugging terminal for T54
    This will be replaced with an executable
    version of bash at some point

    this is really only for debugging the way processes
    launch
*/
#include "io.h"
#include "vga.h"
#include "fs.h"
#include "stdlib.h"
#include "proc.h"
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
    kprintf("[file] -- tries to luanch the specified file");
    kprintf(" ");
}
char buffer[2048];
int b = 0;
char* text = "T54> ";
void termLoop(){
    outb(0x20, 0x20);
    char k;
    k = inb(0x60);
    char final[5048] = {0};
    char keycode = keyboard_map[k];
    if(keycode){
        if(keycode != '\n'){
          buffer[b++] = keycode;
          strcat(final, text);
          strcat(final, buffer);
          strcat(final, "\\r");
          kprintf(final);
        }else{
          strcat(final, text);
          strcat(final, buffer);
          kprintf(final);
          kprintf("Executing...");
          if(strcmp("dir", buffer) == 0){
            kprintf("Directory Listing:");
            for(int i = 0; i < cDirE; i++){
              kprintf(d_entries[i].fileID);
            }
          }else{
            for(int i = 0; i < b; i++){
              if(buffer[i] != '\\' && buffer[i] != "." && buffer[i] != '/')
              buffer[i] -= 32;
            }
            CD_DirectoryEntry* exe = getFile(buffer);
            void (*foo)(void);
            if(exe != NULL){
                uint32_t hello_size = exe->sizeOfExtent;
                uint16_t hello_data[500];
                readFile(exe->fileID, &hello_data);
                foo = (void (*)())&hello_data;
                foo();
            }else{
                kprintf("Failed to find executable");
            }
          }
          // Clear buffer
          for(int i = 0; i < b; i++){
            buffer[i] = 0;
          }
          b = 0;
          // Reprint "T54>"
          char final[128] = {0};
          strcat(final, "T54>");
          strcat(final, "\\r");
          kprintf(final);
        }
    }
    while(!((k >> 7) & 1)){
      k = inb(0x60);
    }
}