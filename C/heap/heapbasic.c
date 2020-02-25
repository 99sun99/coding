//https://blog.csdn.net/duangyhn/article/details/69670609

//header
#define MIN 0  //假设插入值均严格大于0?不是吧？

#ifndef _Heap_H
#define _Heap_H





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



// main programme

#include<stdlib.h>
#include<stdio.h>

struct HeapStruct{
	int size;
	int capacity;
	Item *array;
};

//typedef struct HeapStruct Heapnode;


Heap initial(int size){
	if(size < 8){
		printf("size too small");
		exit(1);
	}

	Heap H;

	H=(Heap)malloc(sizeof(struct HeapStruct));
	if(H==NULL){
		printf("arrange heap fail");
		exit(1);//感觉跟exit更合适，因为没必要向下执行了啊
	}

	H->array=malloc((sizeof(Item))*(size+1));//针对指针的malloc！指上没有哇》 mallo前面不能加指针
	if(H->array==NULL){
		printf("arrange array fail");
		free(H);
		exit(1);
	}
	H->size=0;
	H->capacity=size; //此处为8
	H->array[0]=MIN; //第一位用0占位  算序号的时候好算要么0没法算
	return H;

}

int isEmpty(Heap H){

	return H->size==0 ; //return H->size=0  的部分
}

int isFull(Heap H){
	return H->size==H->capacity;
}

void insert(Item it,Heap H)
{
	if(!isFull(H)){
		H->size++;
		percolateUp(H->size,it,H);//最后一个往前倒
	}
}

//pos delete position

void deleteItem(int pos,Heap H){
	if(!isEmpty(H)){
	  if(pos<1 || pos > H->size)
	    return  ; // return void的意思
	  decreaseKey(pos,H->array[pos]-H->array[1]+1,H);
	  deleteMin(H);//先将其换到最大小，之后用最小值delet ， 放在堆头
	}
}

void deleteMin(Heap H){
	if(!isEmpty(H)){
		percolateDown(1,H->array[H->size--],H); // 如果第一个不是空的，就把第一个拿出来，H->size-- 把第一个放在最后，这时候H->size 就减少了一就不用打印了，
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

	Item it=H->array[pos]-tp;//pos对应的数值减小到arrary[1]-1 的数值 因为是最小堆，放在堆头

	percolateUp(pos,it,H); //向上弹出最小值
}

//key:对应pointer
static void increaseKey(int pos,Item tp,Heap H){
	if(pos<1|| pos>H->size || tp<=0)
	  return ;
	Item it=H->array[pos]+tp; //把pos的关键字增加tp  得到it
	percolateUp(pos,it,H);
}

//it  的pos对应到相应的序列号，it是求值，percolateup是改变序号
static void percolateUp(int pos,Item it,Heap H){
	int i;
	for(i=pos;it < H->array[i/2];i/=2)
	  H->array[i]=H->array[i/2];
	H->array[i]=it;
}


//没有static这里也行吧？不涉及归零问题啊
// void percolateDown(int pos,Item item,Heap H)
//down的方法是反过来，大的往下走走到最后

static  void percolateDown(int pos,Item item,Heap H){
	int i,child;
	for(i=pos,child=i*2;i*2<=H->size;i=child){
		if(child<H->size && H->array[child] > H->array[child+1])
		  child++;   //初始值是child=2i 后面是child++每次赋值给i,
		if(item > H->array[child])
		  H->array[i]=H->array[child];//一直把下面小的赋给i
		else break;
	}
	H->array[i]=item;//最后把i=child大于H->size的这个，用item赋值，<=不会跳出循环的只有大于，这个时候才可以
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
	Heap H=initial(10);
	if(isEmpty(H))
	  printf("H empty\n");

	insert(4,H);
	insert(42,H);
	insert(14,H);
	insert(456,H);
	insert(74,H);
	insert(714,H);
	insert(79,H);
	insert(424,H);

	printHeap(H);
	deleteMin(H);
	printHeap(H);

	deleteItem(5,H);//delete the 3rd one 714

	printHeap(H);






    //puts("now decrese");

	destroy(H);

	return 0;

}
