#ifndef HEAP_H
#define HEAP_H


/**
 堆
 */
typedef struct Heap_
{
  int     size;

  int     (*compare)(const void *key1, const void *key2);
  void    (*destroy)(void *data);

  void    **tree; //tree 指向的类型是 void * 和后面void * data一直，void *data 指针类型是 void*,需要指向类型是void*的指针
  //*tree是数组的意思 指向指针数组的指针
} Heap;


/**
 初始化由参数 heap 所指定堆 - O(1)
 @param heap 堆
 @param compare 函数指针，用于比较两个成员大小（大于返回 1，小于返回 -1，等于返回 0）
 @param destroy 成员析构函数（free...）
 */
void heap_init(Heap *heap,
               int (*compare)(const void *key1, const void *key2),
               void (*destroy)(void *data));


/**
 销毁由参数 heap 所指定堆 - O(n)
 @param heap 堆
 */
void heap_destroy(Heap *heap);


/**
 向堆 heap 中插入一个结点 - O(lg n)
 @param heap 堆
 @param data 结点数据
 @return 插入成功，返回0；否则返回-1
 */
int heap_insert(Heap *heap, const void *data);


/**
 从堆 heap 中释放堆顶部的结点 - O(lg n)
 @param heap 堆
 @param data 已释放结点的存储数据
 @return 释放成功，返回0；否则返回-1
 */
int heap_extract(Heap *heap, void **data);


/**
 由参数 heap 所指定堆中的结点个数 - O(1)
 @param heap 堆
 @return 结点个数
 */
#define heap_size(heap) ((heap)->size)  //npos

#endif /* HEAP_H */


#include <stdlib.h>
#include <string.h>
#include <stdio.h>


//求的是npos的父和子

/**
 获取父结点位置 (i-1)/2
 @param npos 当前结点位置
 @return 父结点位置
 */
#define heap_parent(npos) ((int)(((npos) - 1) / 2))


/**
 获取左子结点位置 i*2+1
 @param npos 当前结点位置
 @return 左子结点位置
 */
#define heap_left(npos) (((npos) * 2) + 1)


/**
 获取右子结点位置 i*2+2
 @param npos 当前结点位置
 @return 右子结点位置
 */
#define heap_right(npos) (((npos) * 2) + 2)


#pragma mark - Public

//直接规定的 struct不是指针就不用分配，maybe,指针指向的地方就不用分配，但是规定块本身的时候就不用malloc,传进来的时候必须有malloc过了，要么传NULL不完了
void heap_init(Heap *heap,
               int (*compare)(const void *key1, const void *key2),
               void (*destroy)(void *data))
{
  //if((heap=(Heap *)malloc(sizeof(Heap)))==NULL)
  //{
   //puts("error");
   //return;
  //}

  /// 初始化堆
  heap->size = 0;
  heap->compare = compare;
  heap->destroy = destroy;
  heap->tree = NULL;

  return;
}


void heap_destroy(Heap *heap) {

  int     i;

  /// 删除所有节点
  if (heap->destroy != NULL) {

    for (i = 0; i < heap_size(heap); i++) {
      /// 执行用户指定的 destroy 函数
      heap->destroy(heap->tree[i]);// **tree; 两层指针才能做到
    }
  }

  /// 删除堆数据 //实际上是所有指针清空的意思
  free(heap->tree);
  /// 清理堆数据结构
  memset(heap, 0, sizeof(Heap));  //整个Heap这么大的地址段都清零的意思

  return;
}


int heap_insert(Heap *heap, const void *data)
{
  void      *temp;
  int       ipos, ppos;

  /// 创建结点空间
  if ((temp = (void **)realloc(heap->tree, (heap_size(heap) + 1) * sizeof (void *))) == NULL) return -1;

  heap->tree = temp;

  /// 将结点插入到最后位置,void 对应void,虽然不加也行，但是void要有自己的type
  heap->tree[heap_size(heap)] = (void *)data;//如果进来时候是0，这个时候是0，+1是把0加上，实际上最后一块
  //的号就是heap->size
//void因为有可能指向任何指针  最下面有例子,void cannot be deleted


  /// 通过将节点上推保障树的平衡
  ipos = heap_size(heap);
  ppos = heap_parent(ipos);

  while (ipos > 0 && heap->compare(heap->tree[ppos], heap->tree[ipos]) < 0) {

    /// 交换当前结点与父结点内容
    temp = heap->tree[ppos];
    heap->tree[ppos] = heap->tree[ipos];
    heap->tree[ipos] = temp;
    //printf("\n----------------------------------------%d\n",temp); //change the pointer address not content;
    /// 将结点向上移动一层保障树的平衡
    ipos = ppos;
    ppos = heap_parent(ipos);//parent 到0即可  ipos为1或者2停止

  }

  /// 更新堆的 size
  heap->size++; //最后改标记要不开头ipos不准了，

  return 0;
}


int heap_extract(Heap *heap, void **data)
{
  void      *save, *temp;
  int       ipos, lpos, rpos, mpos;

  /// 不允许在空堆中释放
  if (heap_size(heap) == 0) return -1;

  /// 释放堆中的顶部节点,传的是地址不是值
  *data = heap->tree[0];//->代表一个*的话，那么左右是*data=*tree[0] 的形式，保证（void **data）最后指针指向的数是value

  /// 调整堆的存储空间
  save = heap->tree[heap_size(heap) - 1];
  // size从1开始

  if (heap_size(heap) - 1 > 0) {

    if ((temp = (void **)realloc(heap->tree, (heap_size(heap) - 1) * sizeof(void *))) == NULL) return -1;

    heap->tree = temp;

    /// 更新堆的 size
    heap->size--;

  } else {

    /// 当释放最后一个结点,和memset不一样是因为后面还要用呢，不用毁了，见后面int main函数实验

    free(heap->tree);
    heap->tree = NULL;
    heap ->size = 0;
    return 0;
  }

  /// 保存最后一个结点的内容到树顶端

  heap->tree[0] = save;

  /// 通过将顶部节点下移保障树的平衡

  ipos = 0;
  lpos = heap_left(ipos);
  rpos = heap_right(ipos);

  while (1) {

    /// 选择与当前结点交换的子结点

    lpos = heap_left(ipos);
    rpos = heap_right(ipos);

    if (lpos < heap_size(heap) && heap->compare(heap->tree[lpos], heap->tree[ipos]) > 0) {

      mpos = lpos;

    } else {

      mpos = ipos;
    }

    if (rpos < heap_size(heap) && heap->compare(heap->tree[rpos], heap->tree[mpos]) > 0) {

      mpos = rpos;
    }

    /// 当 mpos 就是 ipos 时，堆已经完成调整
    if (mpos == ipos) {

      break;

    } else {

      /// 交换当前结点与选择的子结点内容
      temp = heap->tree[mpos];
      heap->tree[mpos] = heap->tree[ipos];
      heap->tree[ipos] = temp;
	  //如果是一个*tree不是**tree那么换这里就达不到改变tree[i]内容的目的了，想改变便tree[i],必须传入的是上一层reference
	  //换的是地址，不是值，换了地址，值也换了，如果直接在tree[i]一层赋值那么交换不过来，
      /// 将结点向下移动一层保障树的平衡
      ipos = mpos;
    }
  }

  return 0;
}





static void print_heap(Heap *heap) //打印当然要打印静态的 不能有变化了
{
  int       i;

  /// 打印堆结构
  fprintf(stdout, "-> Heap size is %d\n", heap_size(heap));

  for (i = 0; i < heap_size(heap); i++) {
    fprintf(stdout, "--> Node=%03d\n", *(int *)heap->tree[i]);  //指向了int型的指针,
    //fprintf(stdout, "Extracting %03d\n", *(int *)data); 比如这里，也是再说，这个地址是指向int的一个指针
    //if (heap_extract(&heap, (void **)&data) != 0) return 1;层级要一样 放进去的时候要的是最底层的地址
  }

  return;
}

//指针类型是什么不一定 ，但是指的类型肯定是一定的，void给指针
static int compare_int(const void *int1, const void *int2)
{
  /// 比较两个整数

  if (*(const int *)int1 > *(const int *)int2) return 1; //指向的是int在地址前面写

  if (*(const int *)int1 < *(const int *)int2) return -1;

  return 0;
}


int main(int argc, char **argv)
{
  Heap      heap;
  void      *data;
  int       intval[30], i;

  /// 初始化堆,compare's function pointer
  heap_init(&heap, compare_int, NULL);

  /// 执行堆操作

  i = 0;

  intval[i] = 5;
  fprintf(stdout, "Inserting %03d\n", intval[i]);
  if (heap_insert(&heap, &intval[i]) != 0) return 1;
  print_heap(&heap);
  i++;

  intval[i] = 10;
  fprintf(stdout, "Inserting %03d\n", intval[i]);
  if (heap_insert(&heap, &intval[i]) != 0) return 1;
  print_heap(&heap);
  i++;

  intval[i] = 20;
  fprintf(stdout, "Inserting %03d\n", intval[i]);
  if (heap_insert(&heap, &intval[i]) != 0) return 1;
  print_heap(&heap);
  i++;

  intval[i] = 1;
  fprintf(stdout, "Inserting %03d\n", intval[i]);
  if (heap_insert(&heap, &intval[i]) != 0) return 1;
  print_heap(&heap);
  i++;

  intval[i] = 25;
  fprintf(stdout, "Inserting %03d\n", intval[i]);
  if (heap_insert(&heap, &intval[i]) != 0) return 1;
  print_heap(&heap);
  i++;

  intval[i] = 22;
  fprintf(stdout, "Inserting %03d\n", intval[i]);
  if (heap_insert(&heap, &intval[i]) != 0) return 1;
  print_heap(&heap);
  i++;

  intval[i] = 9;
  fprintf(stdout, "Inserting %03d\n", intval[i]);
  if (heap_insert(&heap, &intval[i]) != 0) return 1;
  print_heap(&heap);
  i++;

//printf("######################################################################     %d\n",(&heap)->size);


  while (heap_size(&heap) > 0) {
      //data
    if (heap_extract(&heap, (void **)&data) != 0) return 1;//层级要一样
    fprintf(stdout, "Extracting %03d\n", *(int *)data);
    //fprintf(stdout, "Extracting %03d\n", *(int *)*(&data));

    print_heap(&heap);

  }

  /*
//test 还是可以反复用的
 puts("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$");

  intval[i] = 25;
  fprintf(stdout, "Inserting %03d\n", intval[i]);
  if (heap_insert(&heap, &intval[i]) != 0) return 1;
  print_heap(&heap);
  i++;

  intval[i] = 22;
  fprintf(stdout, "Inserting %03d\n", intval[i]);
  if (heap_insert(&heap, &intval[i]) != 0) return 1;
  print_heap(&heap);
  i++;

  intval[i] = 9;
  fprintf(stdout, "Inserting %03d\n", intval[i]);
  if (heap_insert(&heap, &intval[i]) != 0) return 1;
  print_heap(&heap);
  i++;

  printf("######################################################################     %d\n",(&heap)->size);

  while (heap_size(&heap) > 0) {
      //data层级要一样
    if (heap_extract(&heap, (void **)&data) != 0) return 1;
    fprintf(stdout, "Extracting %03d\n", *(int *)data);

    print_heap(&heap);

  }


  */

  /// 销毁堆

  fprintf(stdout, "Destroying the heap\n");
  heap_destroy(&heap);

  return 0;
}


/* understandig pointer in this situation
#include<stdlib.h>



typedef struct HEAP_
{
      int size;

      void **tree;

      int (*compare)( const void *key1,const void *key2);
      void (*destroy) (void *data);
}Heap;

int main()
{
    Heap *H;
    void *temp;

     H=(Heap*)malloc(sizeof(Heap));
     H->tree=NULL;//没有赋值后面就没法realloc,后面没法对应了，循环的时候必须realloc

    if ((temp = (void **)realloc(H->tree, (5) * sizeof (void *))) == NULL) return -1;
    H->tree=temp;

     int *a;  a=1;//int c=1 ,a=&c,  &c指向1, 直接a=1类似char的用法，如果直接*a=2这种情况2没有对应的address会把有用的东西覆盖，指针要初始化！
     int *b;  b=4;

    H->tree[0]=&a;
    H->tree[1]=&b;

    //*(int*)H->tree[0]=0001;
    //*(int*)H->tree[1]=0002;

    printf("%d %d %d %d %d %d\n",H->tree[0],H->tree[1],H->tree,*(int*)H->tree[0],*(int*)H->tree[1],*(int*)*H->tree);
    //对于**tree来说，是一个指向一个指针的指针，对方只有一个指针所以要用++没有[],但是对于*tree来说，是指向一个数组的，insert的时候不是分配了么。
    //如果realloc的temp，是 *tree=temp那么**tree[]才存在
    printf("%d %d %d\n ",*(int*)H->tree[0],*(int*)H->tree[1],*(int*)*H->tree);

    printf("%d %d %d \n",H->tree[0],H->tree[1],*(int*)*(H->tree+1));
    printf(" %d \n",*(int*)*(H->tree+1));
    printf(" %d\n ",*((int*)*H->tree+1));
    printf(" %d\n ",*(int*)*H->tree+1);//1+1=2 not 4

     //printf(" %d %d  ", *(int*)H->tree[0] , *(int*)H->tree[1]);


    return 0;
}


*/

/*
char thinking

#include<stdlib.h>



typedef struct HEAP_
{
      int size;

      void **tree;

      int (*compare)( const void *key1,const void *key2);
      void (*destroy) (void *data);
}Heap;



int main()
{
    Heap *H;
    void *temp;

     H=(Heap*)malloc(sizeof(Heap));
     H->tree=NULL;
    if ((temp = (void **)realloc(H->tree, (5) * sizeof (void *))) == NULL) return -1;
    H->tree=temp;

     char  *a="hello"; //hello分配到*a指向的地址，只有一个指针
    // char  *a[8]; //代表八个指针
    //int (*p)[4]; //指向四维数组的指针
    char   *b="motto";
    char   *c="skr skr";

    H->tree[0]=&a;

    H->tree[1]= b;

     H->tree[2]= &c;


    printf(" %d\n ",  H->tree[0]);
    printf(" %s\n ",  H->tree[1]);
     printf(" %s\n ",  H->tree[1]+6); //对应的是一个字母一个地址，默认前面的识别机制，如果直接是[2]就识别不过来，so指针数组问题的前后默认
    printf(" %s\n ",  H->tree[2]);//6能过来是因为指针类型自动识别了？
    printf(" %s\n ",  H->tree[0]+6);
    printf(" %s\n ", *(int *)(H->tree[0]));
       printf(" %s\n ", *(int *)(H->tree[0])+6);
    printf(" %s\n ", *(int *)(H->tree[0])+12);
       printf(" %d\n ", *(int *)(H->tree[1]));//same address *b's address  b才有string,*b木有！
    printf(" %s\n ", (*(int *)*(H->tree))+1);//ello  指向的是从第一个位置加上去的，如果是  H->tree[0]=a.这句就不行，因为指向第一个的指针，第一个是*tree,
    //**（tree） 最前端挪了一个四字节，就是数组内部，**单个指针总体挪了一步
    printf(" %d\n ", (*(int *)(*(H->tree+1)) ));//same address  *(*tree+1) 指向数组的指针，第二层，挪了一个，以一个数组为单位挪的
    printf(" %s\n ", (*(int *)*(H->tree))+6);//moto
    printf(" %s\n ", (*(int *)*(H->tree))+12);//skr skr     H->tree[2]= &c or   H->tree[2]= c; 均可 赶脚是有自动识别机制。。。

    return 0;
}

*/

/*
#include<stdio.h>
int main()
{
    int a = 10;
    void *ptr = &a;
    printf("%d", *ptr);
    return 0;
}

this version went well
#include<stdio.h>
int main()
{
    int a = 10;
    void *ptr = &a;
    printf("%d", *(int *)ptr);
    return 0;
}

*/


/*
//pointer useage
#include<stdio.h>
int main()
{
    int a = 10;
    void *ptr = &a;//指向的是地址
    //void *ptr;
    //ptr = &a;


    printf("%d", *(int *)ptr);
    return 0;
}


*/

/*指针理解
#include<stdlib.h>

typedef struct Heap_
{
  int     size;

  int     (*compare)(const void *key1, const void *key2);
  void    (*destroy)(void *data);

  void    **tree;
  int     *test;

} Heap;



void heap_init(Heap *heap,
               int (*compare)(const void *key1, const void *key2),
               void (*destroy)(void *data))
{
    heap->size=0;
    heap->compare = compare;
    heap->destroy= destroy;
    heap->tree=NULL;
    //int b;
    //b=2333333;
    //heap->test=b;//-> 本身就是有*的意思
    heap->test=233333;//传的是地址

    return ;
}



int main()
{
    Heap heap;


    heap_init(&heap,NULL,NULL);


    printf("%d  ",(&heap)->size);//right
    printf("%d  ",  (&heap)->test);//right value
    printf("%d  ",  &(&heap)->test);//right address
   //printf("%d  ",(&heap)->size);//wrong


return 0;

}

//还差一个从中间删除





*/
