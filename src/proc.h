/*
    Maybe the hardest part of making this OS,
    process managment (oh no)
*/
#ifndef PROC_H
#define PROC_H
#include "stdint.h"
#include "stdlib.h"
#include "fs.h"
// Process 
typedef struct{
    int PID; // Proc ID (in theory /BIN/INIT should be 0)
} Process;


int runProgram(char* filename);

#endif