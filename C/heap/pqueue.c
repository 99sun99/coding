#include <stdio.h>
#include <stdlib.h>

typedef struct Heap_
{
  int     size;

  int     (*compare)(const void *key1, const void *key2);
  void    (*destroy)(void *data);

  void    **tree;

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
#define heap_size(heap) ((heap)->size)

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


void heap_init(Heap *heap,
               int (*compare)(const void *key1, const void *key2),
               void (*destroy)(void *data))
{
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
      heap->destroy(heap->tree[i]);
    }
  }

  /// 删除堆数据
  free(heap->tree);
  /// 清理堆数据结构
  memset(heap, 0, sizeof(Heap));

  return;
}


int heap_insert(Heap *heap, const void *data)
{
  void      *temp;
  int       ipos, ppos;

  /// 创建结点空间
  if ((temp = (void **)realloc(heap->tree, (heap_size(heap) + 1) * sizeof (void *))) == NULL) return -1;

  heap->tree = temp;

  /// 将结点插入到最后位置
  heap->tree[heap_size(heap)] = (void *)data;

  /// 通过将节点上推保障树的平衡
  ipos = heap_size(heap);
  ppos = heap_parent(ipos);

  while (ipos > 0 && heap->compare(heap->tree[ppos], heap->tree[ipos]) < 0) {

    /// 交换当前结点与父结点内容
    temp = heap->tree[ppos];
    heap->tree[ppos] = heap->tree[ipos];
    heap->tree[ipos] = temp;

    /// 将结点向上移动一层保障树的平衡
    ipos = ppos;
    ppos = heap_parent(ipos);

  }

  /// 更新堆的 size
  heap->size++;

  return 0;
}


int heap_extract(Heap *heap, void **data)
{
  void      *save, *temp;
  int       ipos, lpos, rpos, mpos;

  /// 不允许在空堆中释放
  if (heap_size(heap) == 0) return -1;

  /// 释放堆中的顶部节点
  *data = heap->tree[0];

  /// 调整堆的存储空间
  save = heap->tree[heap_size(heap) - 1];

  if (heap_size(heap) - 1 > 0) {

    if ((temp = (void **)realloc(heap->tree, (heap_size(heap) - 1) * sizeof(void *))) == NULL) return -1;

    heap->tree = temp;

    /// 更新堆的 size
    heap->size--;

  } else {

    /// 当释放最后一个结点

    free(heap->tree);
    heap->tree = NULL;
    heap->size = 0;
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

      /// 将结点向下移动一层保障树的平衡
      ipos = mpos;
    }
  }

  return 0;
}



typedef Heap PQueue;


/**
 初始化由参数 pqueue 所指定优先队列 - O(1)
 @param pqueue 优先队列
 @param compare 函数指针，用于比较两个成员优先级（高于返回 1，低于返回 -1，等于返回 0）
 @param destroy 成员析构函数（free...）
 */
#define pqueue_init heap_init


/**
 销毁由参数 pqueue 所指定优先队列 - O(n)
 @param pqueue 优先队列
 */
#define pqueue_destroy heap_destroy


/**
 在 pqueue 所指定的优先队列中插入一个元素 - O(lg n)
 @param pqueue 优先队列
 @param data 新成员
 @return 插入成功返回0; 已经存在返回1；否则返回-1
 */
#define pqueue_insert heap_insert


/**
 从优先队列 pqueue 中提取优先队列顶部的元素 - O(lg n)
 @param pqueue 优先队列
 @param data 已释放结点的存储数据
 @return 释放成功，返回0；否则返回-1
 */
#define pqueue_extract heap_extract


/**
 获取优先队列 pqueue 中优先级最高元素 - O(1)
 @param pqueue 优先队列
 @return 优先级最高的元素；如果队列为空，那么返回NULL
 */
#define pqueue_peek(pqueue) ((pqueue)->tree == NULL ? NULL : (pqueue)->tree[0])


/**
 优先队列中的元素个数 - O(1)
 @return 元素个数
 */
#define pqueue_size heap_size




static void print_pqueue(PQueue *pqueue)
{
  int     i;

  /// 按顺序打印队列
  fprintf(stdout, "Priority queue size is %d\n", pqueue_size(pqueue));

  for (i = 0; i < pqueue_size(pqueue); i++) {
    fprintf(stdout, "Node=%03d\n", *(int *)pqueue->tree[i]);
  }

  return;
}


static int compare_int(const void *int1, const void *int2)
{
  /// 比较两个整数

  if (*(const int *)int1 > *(const int *)int2) return 1;

  if (*(const int *)int1 < *(const int *)int2) return -1;

  return 0;
}


int main(int argc, char **argv)
{

  PQueue    pqueue;
  void      *data;
  int       intval[30],
  i;

  /// 初始化优先队列
  pqueue_init(&pqueue, compare_int, NULL);

  /// 执行优先队列操作

  i = 0;

  intval[i] = 5;
  fprintf(stdout, "Inserting %03d\n", intval[i]);
  if (pqueue_insert(&pqueue, &intval[i]) != 0) return 1;
  print_pqueue(&pqueue);
  i++;

  intval[i] = 10;
  fprintf(stdout, "Inserting %03d\n", intval[i]);
  if (pqueue_insert(&pqueue, &intval[i]) != 0) return 1;
  print_pqueue(&pqueue);
  i++;

  intval[i] = 20;
  fprintf(stdout, "Inserting %03d\n", intval[i]);
  if (pqueue_insert(&pqueue, &intval[i]) != 0) return 1;
  print_pqueue(&pqueue);
  i++;

  intval[i] = 1;
  fprintf(stdout, "Inserting %03d\n", intval[i]);
  if (pqueue_insert(&pqueue, &intval[i]) != 0) return 1;
  print_pqueue(&pqueue);
  i++;

  intval[i] = 25;
  fprintf(stdout, "Inserting %03d\n", intval[i]);
  if (pqueue_insert(&pqueue, &intval[i]) != 0) return 1;
  print_pqueue(&pqueue);
  i++;

  intval[i] = 22;
  fprintf(stdout, "Inserting %03d\n", intval[i]);
  if (pqueue_insert(&pqueue, &intval[i]) != 0) return 1;
  print_pqueue(&pqueue);
  i++;

  intval[i] = 12;
  fprintf(stdout, "Inserting %03d\n", intval[i]);
  if (pqueue_insert(&pqueue, &intval[i]) != 0) return 1;
  print_pqueue(&pqueue);
  i++;

  while (pqueue_size(&pqueue) > 0) {

    fprintf(stdout, "Peeking at the highest priority element..Value=%03d\n", *(int *)pqueue_peek(&pqueue));
    if (pqueue_extract(&pqueue, (void **)&data) != 0) return 1;
    fprintf(stdout, "Extracting %03d\n", *(int *)data);
    print_pqueue(&pqueue);

  }

  /// 销毁优先队列
  fprintf(stdout, "Destroying the pqueue\n");
  pqueue_destroy(&pqueue);

  return 0;
}


