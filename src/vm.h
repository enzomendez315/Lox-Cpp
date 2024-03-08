#ifndef clox_vm_h
#define clox_vm_h

#include "chunk.h"
#include "value.h"

#define STACK_MAX 256

typedef struct {
    Chunk* chunk;
    uint8_t* ip;    // Instruction pointer
    Value stack[STACK_MAX];
    Value* stackTop;    // Points to where the next value will go
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

/**
 * Adds a value to the stack.
*/
void push(Value value);

/**
 * Retrieves and removes the top value from 
 * the stack.
*/
Value pop();

#endif
