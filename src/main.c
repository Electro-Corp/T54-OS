/*
    Kernel Entrypoint
*/
#include "vga.h"
#include "stdint.h"
#include "stdlib.h"
#include "fs.h"

int testRead();

int testProg = 0;

int kmain(){
    // Init display
    initTerminal();
    kprintf("[Kernel] T54 Display Initilized");

    // Init fs
    initFS();
    // Do a test (if needed)
    //testRead();
    if(testProg == 1){
        // Load object into memory
        CD_DirectoryEntry* hello = getFile("/BIN/HELLO");
        void (*foo)(void);
        if(hello != NULL){
            kprintf("[Kernel] Loading /bin/hello");
            uint32_t hello_size = hello->sizeOfExtent;
            uint16_t hello_data[500];
            readFile(hello->fileID, &hello_data);
            kprintf("[Kernel] Launching /bin/hello");
            foo = (void (*)())&hello_data;
            foo();
        }else{
            kprintf("[Kernel] Failed to find /BIN/HELLO");
        }
        kprintf("[Kernel] /bin/hello finished executing");
    }
    kprintf("[Kernel] Init keyboard handler and basic terminal...");
    kprintf("[Kernel] (in the future hopefully this will be ");
    kprintf("[Kernel]  with a old/minimal version of bash)");
    termInit();
    while(1){
        termLoop(); // TERM
    }
    // should never be reached 
    asm("hlt"); // why is this here?
    // idk deal with it
}   



int testRead(){
    char* fileName = "/README.TXT";
    char printText[512];
    strcat(printText, "[Kernel] Read ");
    strcat(printText, fileName);
    strcat(printText, " as a test..");
    kprintf(printText);
    CD_DirectoryEntry* dir = getFile(fileName);
    if(dir != NULL){
        uint32_t t_size = dir->sizeOfExtent;
        uint16_t t_data[200];
        if(readFile(dir->fileID, &t_data) != -1){
            kprintf((char*)t_data);
            kprintf("[Kernel] Imma just assume that worked since readFile and getFile passed.");
            return 0;
        }
        else{
            kprintf("[Kernel] Failed to read file");
        }
    }else{
        kprintf("[Kernel] File does not exist.");
    }
    return -1;
}