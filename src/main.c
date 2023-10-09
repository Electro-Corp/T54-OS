/*
    Kernel Entrypoint
*/
#include "vga.h"
#include "stdint.h"
#include "stdlib.h"
#include "fs.h"

int testRead();


int kmain(){
    // Init display
    initTerminal();
    kprintf("[Kernel] T54 Display Initilized");
    // Init fs
    initFS();
    // Do a test (if needed)
    //testRead();
    kprintf("[Kernel] Launching /bin/init");
    asm("hlt");
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