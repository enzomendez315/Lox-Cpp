#ifndef clox_vm_h
#define clox_vm_h

#include "chunk.h"

typedef struct {
    Chunk* chunk;
    uint8_t* ip;    // Instruction pointer
} VM;

typedef enum {
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR
} InterpretResult;

/**
 * Initializes a virtual machine.
*/
void initVM();

/**
 * Restores the memory of a virtual machine.
*/
void freeVM();

/**
 * Stores the chunk being executed and runs 
 * the bytecode instructions.
*/
InterpretResult interpret(Chunk* chunk);

#endif
