#include "proc.h"

/*
  Bad function
  dosent create a process just attempts to
  run it directly (dangerous)
*/
int runProcDirect(char* filename){
  CD_DirectoryEntry* exe = getFile(filename);
  // Executable caller
  void (*foo)(void);
  if(exe != NULL){
      // Size of data
      uint32_t hello_size = exe->sizeOfExtent;
      // Buffer for executable
      uint16_t hello_data[500];
      // Read executable data
      readFile(exe->fileID, &hello_data);
      // Check if the file is an AOUT file
      if(hello_data[0] == 7){
        // Yeah its a.out
        // Read location
        uint8_t dTmp[4];
        for(int i = 21; i < 24; i++){
            dTmp[i - 20] = hello_data[i];
        }
        uint32_t jumpTo = little_endian_to_uint32(dTmp);
        foo = (void (*)())jumpTo;
        foo();
      }{
        foo = (void (*)())&hello_data;
        foo();
      }
      return 0;
  }else{
      return -1;
  }
}