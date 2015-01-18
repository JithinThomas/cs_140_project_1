
#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H

#include <inttypes.h>
#include "threads/malloc.h"

#define HEAP_CAPACITY_DEFAULT 64

// Min heap
struct heap {
    void** elems;                   // Elements in the heap
    uint32_t capacity;              // Capacity of the heap, ie, max size possible
    uint32_t size;                  // Number of elements in the heap
    int32_t (*key) (void*);         // Function to generate key from an element
};

typedef struct heap* Heap;

Heap heap_init(int32_t (*) (void*));                // Initialize a new heap
void heap_insert_elem(Heap heap, void* elem);       // Add an element to the heap
void* heap_peek_min(Heap heap);                     // Return the min-element of the heap but do not remove it
void* heap_pop_min(Heap heap);                      // Return the min-element of the heap and remove it
void heap_double_capacity(Heap heap);               // Increase capacity of the heap
void heap_swap_elems(Heap heap, uint32_t idx1, uint32_t idx2);      // Swap two elements of the heap

struct test_node {
    int32_t elem;
    int32_t dummy_data;
};

typedef struct test_node* Node;

#endif
