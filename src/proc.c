#include "proc.h"
int runProgram(char* filename){
  CD_DirectoryEntry* exe = getFile(filename);
  void (*foo)(void);
  if(exe != NULL){
      uint32_t hello_size = exe->sizeOfExtent;
      uint16_t hello_data[500];
      readFile(exe->fileID, &hello_data);
      foo = (void (*)())&hello_data;
      foo();
      return 0;
  }else{
      return -1;
  }
}