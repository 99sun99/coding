#include "heap.h"

#include <stdlib.h>

struct Heap {
    int capacity;
    int size;
    int *heap;
    int type;
};

Heap *heapCreate(HeapType type) {
    Heap *h;

    h = malloc(sizeof(Heap));
    if(!h)
        return NULL;

    h->capacity = 16;
    h->size = 0;
    h->heap = malloc(sizeof(int) * h->capacity);
    h->type = type;
}

void heapDestroy(Heap *h) {
    free(h->heap);
    free(h);
}

void heapInsert(Heap *h, int value) {
    int *newHeap;
    int i, j;

    if(h->size == h->capacity) {
        newHeap = realloc(h->heap, sizeof(int) * h->capacity * 2);
        if(!newHeap)
            return;
        h->capacity *= 2;
        h->heap = newHeap;
    }

    h->heap[h->size++] = value;

    i = h->size - 1;
    j = (i - 1) / 2;
    while(h->heap[i] * h->type < h->heap[j] * h->type) {
        h->heap[i] ^= h->heap[j];
        h->heap[j] ^= h->heap[i];
        h->heap[i] ^= h->heap[j];
        i = j;
        j = (i - 1) / 2;
    }
}

int heapExtract(Heap *h) {
    int ret = h->heap[0];
    int l, r;
    int i = 0, j, k, swap;

    if(h->size == 1)
        return h->heap[--h->size];

    else if(h->size == 2) {
        h->heap[0] = h->heap[--h->size];
        return ret;
    }

    h->heap[0] = h->heap[--h->size];
    l = h->heap[0] - h->heap[1];
    r = h->heap[0] - h->heap[2];
    j = 1;
    k = 2;

    while(l * h->type > 0 && j < h->size || r * h->type > 0 && k < h->size) {
        if(l * h->type > r * h->type)
            swap = j;

        else if(r * h->type > l * h->type)
            swap = k;

        h->heap[i] ^= h->heap[swap];
        h->heap[swap] ^= h->heap[i];
        h->heap[i] ^= h->heap[swap];

        i = swap;

        j = i * 2 + 1;
        k = i * 2 + 2;

        l = h->heap[i] - h->heap[j];
        r = h->heap[i] - h->heap[k];
    }

    return ret;
}

int heapEmpty(Heap *h) {
    return h->size == 0;
}
