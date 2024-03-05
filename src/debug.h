#ifndef clox_debug_h
#define clox_debug_h

#include "chunk.h"

/**
 * Prints each instruction that is part of the chunk.
*/
void disassembleChunk(Chunk* chunk, const char* name);

/**
 * Prints the byte offset of the given instruction, then 
 * reads the opcode and prints it.
*/
int disassembleInstruction(Chunk* chunk, int offset);

#endif