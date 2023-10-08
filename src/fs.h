/*
    Filesystem handler
*/
#ifndef FS_H
#define FS_H
#include "vga.h"
#include "cd.h"

typedef struct {
    // Volume ID
    char CD_volID[32];

} CD_FS;


typedef struct {
    char fileID[256];
    uint32_t locOfExtent;
    uint32_t sizeOfExtent;

    int tmp;
    //CD_DirectoryEntry* nextEntry;
} CD_DirectoryEntry;

// FS's
CD_FS rootMedia;

static CD_DirectoryEntry d_entries[256];
static int cDirE = 0; // current index of directory index being loaded

void initFS();

void initCDFS();

int readFile(char* filePath, uint8_t* buffer);

CD_DirectoryEntry* getFile(char* filePath);

#endif