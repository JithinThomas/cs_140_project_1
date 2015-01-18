
#include "datastructures.h"
#include <stdlib.h>

Heap heap_init(int32_t (*key) (void*)) {
    Heap heap = (Heap) malloc (sizeof(struct heap));
    heap->elems = (void**) malloc (HEAP_CAPACITY_DEFAULT * sizeof(void*));
    heap->capacity = HEAP_CAPACITY_DEFAULT;
    heap->size = 0;
    heap->key = key;

    return heap;
}

void heap_double_capacity(Heap heap) {  
    void** elems_copy = (void**) malloc (heap->capacity * 2 * sizeof(void*));
    uint32_t i;
    for (i = 1; i <= heap->size; i++) {
        elems_copy[i] = heap->elems[i];
    }

    void** tmp = heap->elems;
    heap->elems = elems_copy;
    free(tmp);

    heap->capacity *= 2;
}

void heap_insert_elem(Heap heap, void* elem) {
    if (heap->capacity == heap->size + 1) {     // Since index 0 is not used
        heap_double_capacity(heap);
    }

    heap->elems[heap->size + 1] = elem;
    heap->size++;

    if (heap->size > 1) {
        uint32_t child_idx = heap->size;
        uint32_t parent_idx = child_idx / 2;
        while(parent_idx > 0) {
            int32_t parent_key = heap->key(heap->elems[parent_idx]);
            int32_t child_key = heap->key(heap->elems[child_idx]);
            if (child_key >= parent_key) {
                return;
            }

            heap_swap_elems(heap, parent_idx, child_idx);
            child_idx = parent_idx;
            parent_idx = child_idx / 2;
        }
    }
}

void* heap_peek_min(Heap heap) {
    if (heap->size == 0) {
        return NULL;
    }

    return heap->elems[1];
}

void* heap_pop_min(Heap heap) {
    if (heap->size == 0) {
        return NULL;
    }

    void* min_elem = heap->elems[1];

    if (heap->size > 1) {
        void** elems = heap->elems;
        elems[1] = elems[heap->size];
        elems[heap->size] = NULL;
        heap->size--;

        uint32_t parent_idx = 1;
        uint32_t left_idx = parent_idx * 2;

        while (left_idx <= heap->size) {
            int32_t parent_key = heap->key(elems[parent_idx]);
            int32_t left_key = heap->key(elems[left_idx]);
            uint32_t min_idx = (left_key < parent_key) ? left_idx : parent_idx;
            int32_t min_key = (left_key < parent_key) ? left_key : parent_key;
            uint32_t right_idx = left_idx + 1;

            if (right_idx <= heap->size) {
                int32_t right_key = heap->key(elems[right_idx]);
                min_idx = (right_key < min_key) ? right_idx : min_idx;
            }

            if (min_idx == parent_idx) {
                return min_elem;
            }

            heap_swap_elems(heap, min_idx, parent_idx);
            parent_idx = min_idx;
            left_idx = min_idx * 2;
        }
    }

    return min_elem;
}

void heap_swap_elems(Heap heap, uint32_t idx1, uint32_t idx2) {
    if ((idx1 <= heap->size) && (idx2 <= heap->size)) {
        void* tmp = heap->elems[idx1];
        heap->elems[idx1] = heap->elems[idx2];
        heap->elems[idx2] = tmp;
    }
}
