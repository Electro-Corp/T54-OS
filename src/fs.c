/*
    FS
*/
#include "fs.h"
#include "stdint.h"
#include "string.h"
// From the BIOS data sector
const unsigned short *hard_disks_ptr = (const unsigned short*) 0x0475;
#define NULL ((void *)0)
uint8_t i_hdds = 0;


void initFS(){
    kprintf("[KFS] Initilizing FS");
    kprintf("[KFS] Retriving number of drives");
    i_hdds = *hard_disks_ptr;

    switch(i_hdds){
        case 0:
            kprintf("[KFS] No disks installed");
            kprintf("[KFS] No HDD installed, installation to disk is disabled.");
            break;
        case 1:
            kprintf("[KFS] 1 disk installed");
            break;
        case 2:
            kprintf("[KFS] 2 disks installed");
            break;
        case 3:
            kprintf("[KFS] 3 disks installed");
            break;
        case 4:
            kprintf("[KFS] 4 disks installed");
            break;
        default:
            kprintf("[KFS] 4+ disks installed");
            break;
    }
    
    // Init read from CD-DRIVE
    initCDFS();
    return;
}

uint32_t little_endian_to_uint32(uint8_t* bytes) {
	uint32_t value = 0;
	for (int i = 0; i < 4; i++) {
		value |= bytes[i] << (i * 8);
	}
	return value;
}

void initCDFS(){
    kprintf("[KFS] Init root FS from CD-ROM Drive");
    kprintf("[KFS] This FS will be non-writable, and can only be used");
    kprintf("      to run programs from /bin");
    uint8_t pvd[2048];
	  int c = read_cdrom(0x1F0, 0, 16, 1, &pvd);
    kprintf("[KFS] Read PVD");
    // Read drive label
    int labelOffset = 40; // Starts at offset 40, size of 32
    for(int i = labelOffset; i < labelOffset + 31; i++){
        rootMedia.CD_volID[i - labelOffset] = (char) pvd[i];
    }
    // Read root directory location
    int rootOffset = 156;
    uint8_t tmp[4];
    for(int i = rootOffset + 2; i < rootOffset + 6; i++){
        tmp[i - (rootOffset + 2)] = pvd[i];
    }
    uint32_t r_extentLBA = little_endian_to_uint32(tmp);
    for(int i = rootOffset + 10; i < rootOffset + 14; i++){
        tmp[i - (rootOffset + 10)] = pvd[i];
    }
    uint32_t r_extentSize = little_endian_to_uint32(tmp);

    int idSize = pvd[rootOffset + 32];
  
    char id[256];
    for(int i = rootOffset + 33; i < idSize; i++){
        id[i - (rootOffset + 33)] = pvd[i];
    }

    CD_DirectoryEntry root = {id, r_extentLBA, r_extentSize, 0};
    d_entries[cDirE] = root;

    uint8_t data[2048];
    read_cdrom(0x1F0, 0, r_extentLBA, 1, &data);

    kprintf("================================");
    char listText[512];
    strcat(listText, "[KFS] Directory listing for '");
    strcat(listText, rootMedia.CD_volID);
    strcat(listText, "'");
    kprintf(listText);
    readDirectory(data, "/");
    // Print out directories/files
    /*int c_Offset = 33;
    for(int i = 0; i < 4; i++){
      char Tid[256];
      idSize = data[c_Offset - 1];
      for(int i = c_Offset; i < idSize; i++){
          Tid[i - c_Offset] = data[i];
      }
      kprintf(Tid);
      c_Offset += idSize + 1;
    }*/
    
    kprintf("================================");
    
  // 7
    char* fileName = "/BOOT/GRUB/MENU.LST";
    uint32_t t_size = getFile(fileName)->sizeOfExtent;
    uint8_t t_data[t_size];
    if(readFile(fileName, &t_data) != -1)
    kprintf(t_data);
    else
    kprintf("Failed to read file");
    return;
}


void readDirectoryEntry(){
  
}

void readDirectory(uint8_t* data, char* dirs){
  int currentpos = 000;
  for(int i = 0; i < 256; i++){
    int flags = data[currentpos + 25];
    int idSize = data[currentpos + 32];
    char Tid[256];
    for(int i = 0; i < idSize && data[i + currentpos + 33] != ';'; i++){
        if((flags >> 1) & 1 == 1 || data[i + currentpos + 34] == ';'){
          if(data[i + currentpos + 33] == '.') break;
        }
        Tid[i] = data[i + currentpos + 33];
    }
    // Retrieve data
    uint8_t dTmp[4];
    for(int i = currentpos + 2; i < currentpos + 6; i++){
        dTmp[i - (currentpos + 2)] = data[i];
    }
    uint32_t lba = little_endian_to_uint32(dTmp);
    for(int i = currentpos + 10; i < currentpos + 14; i++){
        dTmp[i - (currentpos + 10)] = data[i];
    }
    uint32_t size = little_endian_to_uint32(dTmp);
    
    char fullPath[1024] = {0};
    if(idSize > 1){
      strcat(fullPath, dirs);
      strcat(fullPath, Tid);
      if((flags >> 1) & 1 == 1)
        strcat(fullPath, "/");
      
      CD_DirectoryEntry d = {fullPath, lba, size, 0};
      strcpy(d.fileID, fullPath);
      d.locOfExtent = lba;
      d.sizeOfExtent = size;
      cDirE++;
      d_entries[cDirE] = d;

      kprintf(d_entries[cDirE].fileID);
    }
    
    // Check if its a sub-directory
    
    if((flags >> 1) & 1 == 1 && idSize > 1){
      uint8_t m_data[2048];
      read_cdrom(0x1F0, 0, lba, 1, &m_data);
      readDirectory(m_data, fullPath);
    }
    
    if(data[currentpos] == 0)break;
    currentpos += data[currentpos];
  }
}


int readFile(char* filePath, uint8_t* buffer){
  // Scan for file
  CD_DirectoryEntry* tmp = getFile(filePath);
  if(tmp != NULL){
    int secs = 1;
    if(tmp->sizeOfExtent / 2048 > 1) secs = tmp->sizeOfExtent / 2048;
    read_cdrom(0x1F0, 0, tmp->locOfExtent, secs, &buffer);
    return 0; 
  }
  return -1;
}

CD_DirectoryEntry* getFile(char* filePath){
  for(int i = 0; i <= cDirE; i++){
    if(strcmp(filePath, d_entries[i].fileID) == 0){
      return &(d_entries[i]);
    }
  }
  return NULL;
}