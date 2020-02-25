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




int heap_random_extract(Heap *heap, void **data,int i)
{
  void      *save, *temp;
  int       ipos, lpos, rpos, mpos;

  /// 不允许在空堆中释放
  if (heap_size(heap) == 0) return -1;

  /// 释放堆中的顶部节点,传的是地址不是值
  *data = heap->tree[i];//->代表一个*的话，那么左右是*data=*tree[0] 的形式，保证（void **data）最后指针指向的数是value

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

  heap->tree[i] = save;

  /// 通过将顶部节点下移保障树的平衡

  ipos = i;
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

  intval[i] = 25;
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

  intval[i] = 5;
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


int x=0;
int m[7]={0,1,1,3,1,1,0};


  while (heap_size(&heap) > 0) {
     // m=rand()%(heap_size(&heap)+1);
     // printf("m=%d\n",m);

     printf("x=%d\n",m[x]);

    if (heap_random_extract(&heap, (void **)&data,m[x]) != 0) return 1;//层级要一样
    fprintf(stdout, "Extracting %03d\n", *(int *)data);
    //fprintf(stdout, "Extracting %03d\n", *(int *)*(&data));

    print_heap(&heap);
    x++;

  }


  /// 销毁堆

  fprintf(stdout, "Destroying the heap\n");
  heap_destroy(&heap);

  return 0;
}






/*

要让随机数限定在一个范围，可以采用模除加加法的方式。
要产生随机数r， 其范围为 m<=r<=n，可以使用如下公式：
rand()%(n-m+1)+m
其原理为，对于任意数，
0<=rand()%(n-m+1)<=n-m
于是
0+m<=rand()%(n-m+1)+m<=n-m+m
即
m<=rand()%(n-m+1)+m<=n


*/


