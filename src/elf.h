/*
    Parse ELF files
*/
#ifndef ELF_H
#define ELF_H

#include "fs.h"
#include "stdlib.h"

typedef struct{
    char header[4];
    char bit32;
    char endian;
    char version;
    char OSABI;
    char ABIVER;
    char padBytes[7]; // ignore
    int type;
    int machine;
    int e_version;
    int entryPoint;
    int headTableLoc;
    int sectionHeadLoc;
    int flags;
    int headSize;
    int phentSize;
    char phNum[2];
    char shNum[2];
    char secNameLoc[2];
} ELF_Header;

typedef struct {
    int type;
    int offset;
    int vMemSeg;
    int pSegAddr;
    int size;
    int memSize;
    int flags;
    int align;
} ELF_Prog_Header;

char elf_header[4] = {0x7F, 0x45, 0x4c, 0x46};

int readELFFile(char* file);

#endif