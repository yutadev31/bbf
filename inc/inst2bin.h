#ifndef _H_INST2BIN_
#define _H_INST2BIN_

#include <parser.h>

#define MEMORY_SIZE 64
#define BIN_SIZE 4096

void inst2bin(Instruction *root, unsigned char *bin, int *binIndex, unsigned char *memory, int *pointer);

#endif
