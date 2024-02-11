#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"

/**
 * Contains a list of all the opcodes.
*/
typedef enum {
    OP_RETURN,      // Returns from the current function
} OpCode;

/**
 * Represents a dynamic array of instructions.
*/
typedef struct {
    int count;      // Elements in the array
    int capacity;   // Entries allocated in the array
    uint8_t* code;
} Chunk;

/**
 * Initializes a new chunk.
*/
void initChunk(Chunk* chunk);

/**
 * Appends a byte to the end of the array.
*/
void writeChunk(Chunk* chunk, uint8_t byte);

/**
 * Deallocates all the memory and leaves the chunk 
 * in a well-defined empty state.
*/
void freeChunk(Chunk* chunk);

#endif