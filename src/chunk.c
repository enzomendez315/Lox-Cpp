#include <stdlib.h>

#include "chunk.h"
#include "memory.h"

void initChunk(Chunk* chunk) {
    chunk->count = 0;
    chunk->capacity = 0;
    chunk->code = NULL;
}

void writeChunk(Chunk* chunk, uint8_t byte) {
    // Resize array if necessary
    if (chunk->capacity < chunk->count + 1) {
        int oldCapacity = chunk->capacity;
        chunk->capacity = GROW_CAPACITY(oldCapacity);
        chunk->code = GROW_ARRAY(uint8_t, chunk->code, oldCapacity, chunk->capacity);
    }

    // Store byte
    chunk->code[chunk->count] = byte;
    chunk->count++;
}

void freeChunk(Chunk* chunk) {
    // Deallocate memory
    FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
    // Restore the state of the chunk to empty
    initChunk(chunk);
}