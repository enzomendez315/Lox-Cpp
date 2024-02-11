#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"

typedef enum {
    OP_RETURN,  // Returns from the current function.
} OpCode;

typedef struct {
    int count;  // Elements that are in use.
    int capacity;   // Entries allocated in the array.
    uint8_t* code;
} Chunk;

void initChunk(Chunk* chunk);
void writeChunk(Chunk* chunk, uint8_t byte);

#endif