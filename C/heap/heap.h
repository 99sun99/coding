#ifndef _Heap_H
#define _Heap_H

#define MIN 0                                                       //假设插入值均严格大于0

struct HeapStruct;
typedef struct HeapStruct *Heap;
typedef int Item;

Heap initial(int size);
int isEmpty(Heap H);
int isFull(Heap H);
void insert(Item it,Heap H);
void deleteItem(int pos,Heap H);
void deleteMin(Heap H);
void destroy(Heap H);

static void decreaseKey(int pos,Item tp,Heap H);
static void increaseKey(int pos,Item tp,Heap H);
static void percolateUp(int pos,Item it,Heap H);
static void percolateDown(int pos,Item it,Heap H);

#endif

struct HeapStruct{
	int size;
	int capacity;
	Item *array;
};
