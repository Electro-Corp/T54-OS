/*
    FS
*/
#include "fs.h"
#include "stdint.h"
// From the BIOS data sector
const unsigned short *hard_disks_ptr = (const unsigned short*) 0x0475;

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
    for(int i = rootOffset + 10; i < rootOffset + 16; i++){
        tmp[i - (rootOffset + 10)] = pvd[i];
    }
    uint32_t r_extentSize = little_endian_to_uint32(tmp);

    char id[256];
    for(int i = rootOffset + 33; pvd[i] != ';' && i < 256 && pvd[i] != 0; i++){
        id[i - (rootOffset + 33)] = pvd[i];
    }

    CD_DirectoryEntry root = {id, r_extentLBA, r_extentSize, 0};
    d_entries[cDirE] = root;
    // Ok now lets recursivly load them in  
    for(int i = 0; i < 2; i++){
        uint8_t data[2048];
        read_cdrom(0x1F0, 0, d_entries[cDirE].locOfExtent + (d_entries[cDirE].locOfExtent / 2048), 1, &data);
        char id[256];
        for(int i = 33; data[i] != ';' && i < 256 && data[i] != 0; i++){
            id[i - (33)] = data[i];
        }
        kprintf(id);
        for(int i = 2; i < 6; i++){
            tmp[i - 2] = data[i];
        }
        uint32_t r_extentLBA = little_endian_to_uint32(tmp);
        for(int i = 10; i < 16; i++){
            tmp[i - 10] = data[i];
        }
        uint32_t r_extentSize = little_endian_to_uint32(tmp);
        cDirE++;
        CD_DirectoryEntry goof = {r_extentLBA, r_extentSize, id};
        d_entries[cDirE] = goof;
    }

    /*uint8_t tmp[4];
    for(int i = pathOffset; i < pathOffset + 3; i++){
        tmp[i - pathOffset] = pvd[i];
    }
    rootMedia.rootDirEntr = little_endian_to_uint32(&tmp);
    // Read root dir record
    uint8_t pT1[140]; 
	c = read_cdrom(0x1F0, 0, rootMedia.rootDirEntr, 1, &pT1);
    char dirID[16];
    for(int i = 15; i < 30; i++){
        dirID[i - 15] = pT1[i];
    }
    kprintf(dirID);*/
    kprintf("[KFS] Root Media label:");
    kprintf(rootMedia.CD_volID);

}