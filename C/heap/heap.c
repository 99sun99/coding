#include"heap.h"

#include<stdlib.h>
#include<stdio.h>

Heap initial(int size){
	if(size < 8){
		printf("size too small");
		exit(1);
	}

	Heap H;
	H=malloc(sizeof(struct HeapStruct));
	if(H==NULL){
		printf("arrange heap fail");
		exit(1);
	}

	H->array=malloc(sizeof(Item)*(size+1));
	if(H->array==NULL){
		printf("arrange array fail");
		free(H);
		exit(1);
	}
	H->size=0;
	H->capacity=size;
	H->array[0]=MIN;
	return H;

}

int isEmpty(Heap H){

	return H->size==0;
}

int isFull(Heap H){
	return H->size==H->capacity;
}

void insert(Item it,Heap H){
	if(!isFull(H)){
		H->size++;
		percolateUp(H->size,it,H);
	}
}

void deleteItem(int pos,Heap H){
	if(!isEmpty(H)){
	  if(pos<1 || pos > H->size)
	    return ;
	  decreaseKey(pos,H->array[pos]-H->array[1]+1,H);
	  deleteMin(H);
	}
}

void deleteMin(Heap H){
	if(!isEmpty(H)){
		percolateDown(1,H->array[H->size--],H);
	}

}

void destroy(Heap H){
	if(H!=NULL){
		free(H->array);
		free(H);
		H=NULL;
	}
}

static void decreaseKey(int pos,Item tp,Heap H){
	if(pos<1|| pos>H->size || tp<=0)
	  return ;
	Item it=H->array[pos]-tp;
	percolateUp(pos,it,H);
}

static void increaseKey(int pos,Item tp,Heap H){
	if(pos<1|| pos>H->size || tp<=0)
	  return ;
	Item it=H->array[pos]+tp;
	percolateUp(pos,it,H);
}

static void percolateUp(int pos,Item it,Heap H){
	int i;
	for(i=pos;it < H->array[i/2];i/=2)
	  H->array[i]=H->array[i/2];
	H->array[i]=it;
}

static void percolateDown(int pos,Item item,Heap H){
	int i,child;
	for(i=pos,child=i*2;i*2<=H->size;){
		if(child<H->size && H->array[child] > H->array[child+1])
		  child++;
		if(item > H->array[child])
		  H->array[i]=H->array[child];
		else break;

		i = child;
	}

	H->array[i]=item;
}

void printHeap(Heap H){
	int i;
	if(!isEmpty(H)){
		for(i=1;i<=H->size;i++)
		  printf("%d\t",H->array[i]);
		printf("\n");
	}
}



int main(){
	Heap H=initial(12);
	if(isEmpty(H))
	  printf("H empty\n");

	insert(38,H);
	insert(42,H);
	insert(14,H);
	insert(456,H);
	insert(47,H);
	insert(74,H);
	insert(714,H);
	insert(35,H);
	insert(6,H);
	printHeap(H);

	//deleteMin(H);
	//printHeap(H);

	deleteItem(5,H);
	printHeap(H);

	destroy(H);

     return 0;
}
