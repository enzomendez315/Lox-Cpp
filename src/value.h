#ifndef clox_value_h
#define clox_value_h

#include "common.h"

typedef double Value;

/**
 * Represents a dynamic array of values.
*/
typedef struct {
    int capacity;
    int count;
    Value* values;
} ValueArray;

/**
 * Initializes a value array.
*/
void initValueArray(ValueArray* array);

/**
 * Puts a value in the value array.
*/
void writeValueArray(ValueArray* array, Value value);

/**
 * Frees the memory in the value array.
*/
void freeValueArray(ValueArray* array);

#endif