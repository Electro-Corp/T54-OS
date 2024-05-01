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
/*
    Sets up keyboard and prints out
    init text
*/
void termInit(){
    // Enable keyboard interrupt
    unsigned char curmask_master = inb(0x21);
    outb(0x21, curmask_master & 0xFD);
    // Print intro text
    kprintf("==================================");
    kprintf("        T54 DEBUG TERMINAL        ");
    kprintf("==================================");
    kprintf("Used for debugging purposes and launching programs.");
    kprintf("Commands:");
    kprintf("dir -- Lists all directories and files");
    kprintf("[file] -- tries to luanch the specified file");
    kprintf("cat - enables cat mode, next [file] given to terminal will be printed");
    kprintf(" ");
}
char buffer[2048];
int b = 0;
char* text = "T54> ";
char k;
char keycode;
int cat = 0;
void termLoop(){
    //outb(0x20, 0x20);
    k = inb(0x60);
    char final[5048] = {0};
    keycode = keyboard_map[k];
    if(keycode){
        if(keycode == '\b'){
          if(b > 0)
            buffer[b--] = 0;
          strcat(final, text); 
          strcat(final, buffer);
          strcat(final, "\\r"); // Make it print on the same line
          kprintf(final);
        }
        else if(keycode != '\n'){
          buffer[b++] = keycode;
          strcat(final, text);
          strcat(final, buffer);
          strcat(final, "\\r"); // Make it print on the same line
          kprintf(final);
        }else{
          strcat(final, text);
          strcat(final, buffer);
          kprintf(final);
          if(strcmp("dir", buffer) == 0){
            for(int i = 2; i < getNumOfDirs(); i++){
              kprintf(getDirs()[i].fileID);
            }
          }else if(strcmp("cat", buffer) == 0){
            cat = 1;
            kprintf("cat enabled, next file on term will printed out");
          }else{
            for(int i = 0; i < b; i++){
              // The CD FS has everything captalized so like
              // lets do that
              if(buffer[i] != '\\' && buffer[i] != "." && buffer[i] != '/')
              buffer[i] -= 32;
            }
            if(readELFFile(buffer) == 0){
              kprintf("ELF File executed");
            }else{
              CD_DirectoryEntry* exe = getFile(buffer);
              void (*foo)(void);
              if(exe != NULL){
                  uint32_t hello_size = exe->sizeOfExtent;
                  uint16_t hello_data[hello_size];
                  readFile(exe->fileID, &hello_data);
                  if(cat == 0){
                    foo = (void (*)())&hello_data;
                    foo();
                  }else{
                    kprintf((char*)hello_data);
                    cat = 0;
                  }
              }else{
                  kprintf("Failed to find executable");
              }
            }
            /*if(runProcDirect(buffer) == -1){
                kprintf("File failed to execute or does not exist");    
            }*/
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