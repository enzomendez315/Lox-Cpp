#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"
#include "value.h"

/**
 * Contains a list of all the opcodes.
*/
typedef enum {
    OP_CONSTANT,    // Stores a constant value
    OP_ADD,
    OP_SUBTRACT,
    OP_MULTIPLY,
    OP_DIVIDE,
    OP_NEGATE,
    OP_RETURN,      // Returns from the current function
} OpCode;

/**
 * Represents a dynamic array of instructions.
*/
typedef struct {
    int count;      // Elements in the array
    int capacity;   // Entries allocated in the array
    uint8_t* code;
    int* lines;     // Stores the source line of each byte
    ValueArray constants;   // Holds constant identifiers
} Chunk;

/**
 * Initializes a new chunk.
*/
void initChunk(Chunk* chunk);

/**
 * Appends a byte (an opcode or an operand) to the end 
 * of the array.
*/
void writeChunk(Chunk* chunk, uint8_t byte, int line);

/**
 * Adds a new constant to the chunk and returns the 
 * index where the constant was appended.
*/
int addConstant(Chunk* chunk, Value value);

/**
 * Deallocates all the memory and leaves the chunk 
 * in a well-defined empty state.
*/
void freeChunk(Chunk* chunk);

#endif