#ifndef HEAP_H
#define HEAP_H

typedef struct Heap Heap;

typedef enum {
    MAX_HEAP = -1,
    MIN_HEAP = 1,
} HeapType;

Heap *heapCreate(HeapType type);
void heapDestroy(Heap *heap);

void heapInsert(Heap *heap, int value);
int heapExtract(Heap *heap);

int heapEmpty(Heap *h);

#endif /* HEAP_H */
