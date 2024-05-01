#include "elf.h"

int readELFFile(char* file){
    kprintf(file);
    CD_DirectoryEntry* exe = getFile(file);
    if(exe){
        uint32_t elf_size = exe->sizeOfExtent;
        uint16_t elf_data[elf_size];
        readFile(exe->fileID, &elf_data);
        if(memcmp(&elf_header, &elf_data, 4) == 0){
            kprintf("ELF file!");
            // start doin stuff
            
            // Read header
            ELF_Header head;
            memcpy(&head, &elf_data, 52);
            char buf[5];
            itoa(head.phentSize, 10, buf);
            kprintf(buf);
            // Read
            ELF_Prog_Header progHead;
            memcpyBounded(&progHead, &elf_data, head.headTableLoc, head.phentSize);
            
            switch((progHead.type)){
                case 0x00000000:
                    kprintf("NULL");
                    break;
                case 0x00000002:
                 	kprintf("PT_DYNAMIC Dynamic linking information.");
                    break;
                case 0x00000003:
                 	kprintf("PT_INTERP Interpreter information.");
                    break;
                case 0x00000004:
                 	kprintf("PT_NOTE Auxiliary information.");
                    break;
                case 0x00000005:
                 	kprintf("PT_SHLIB Reserved.");
                    break;
                case 0x00000006:
                 	kprintf("PT_PHDR Segment containing program header table itself.");
                    break;
                case 0x00000007:
                 	kprintf("PT_TLS Thread-Local Storage template."); 
                    break;
                case 0x00000001:
                    kprintf("Loadable segment");
                    break;
                default: 
                    kprintf("IDK man");
                    break;
            }

            return 0;
        }else{
            kprintf("NOT AN ELF FILE");
            return 1;
        }
        
    }else{
        kprintf("File not found!");
        return -1;
    }
    return 0;
}