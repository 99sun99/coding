#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")
//#include <netinet/in.h>  //百度解决方案是上面两句
#include <limits.h>
#include <stdlib.h>
#include <string.h>
typedef struct BiTreeNode_
{
  void               *data;
  struct BiTreeNode_ *left;
  struct BiTreeNode_ *right;

} BiTreeNode;











/**
 由参数 tree 所指定二叉树中的结点个数 - O(1)
 @param tree 二叉树
 @return 结点个数
 */
#define bitree_size(tree) ((tree)->size)


/**
 返回由参数 tree 所指定二叉树的根结点 - O(1)
 @param tree 二叉树
 @return 根结点
 */
#define bitree_root(tree) ((tree)->root)


/**
 判断由参数 node 所标识结点是否为二叉树中某个分支的结束 - O(1)
 @param node 待判断结点
 @return 分支结束则返回1；否则返回0
 */
#define bitree_is_eob(node) ((node) == NULL)


/**
 判断由参数 node 所指定结点是否为二叉树中的叶子结点 - O(1)
 @param node 待判断结点
 @return 叶子结点返回1；否则返回0
 */
#define bitree_is_leaf(node) ((node)->left == NULL && (node)->right == NULL)


/**
 返回由参数 node 所指定结点中存储的数据 - O(1)
 @param node 指定结点
 @return 结点中存储的数据
 */
#define bitree_data(node) ((node)->data)


/**
 返回由参数 node 所指定结点的左子结点 - O(1)
 @param node 指定结点
 @return 指定结点的左子结点
 */
#define bitree_left(node) ((node)->left)


/**
 返回由参数 node 所指定结点的右子结点 - O(1)

 @param node 指定结点
 @return 指定结点的右子结点
 */
#define bitree_right(node) ((node)->right)
/**
 二叉树
 */
typedef struct BiTree_
{
  int         size;

  int         (*compare)(const void *key1, const void *key2);
  void        (*destroy)(void *data);

  BiTreeNode  *root;

} BiTree;

int bit_get(const unsigned char *bits, int pos);


/**
 设置缓冲区 bits 中处于位置 pos 的位的状态为 state - O(1)
 @param bits 缓冲区
 @param pos 位置 (缓冲区最左边的位置为 0 )
 @param state 状态值（必须为 0 或 1 ）
 */
void bit_set(unsigned char *bits, int pos, int state);


/**
 按位计算两个缓冲区 bits1 与 bits2 的异或值 - O(β) β 为每个缓冲区中位的个数
 @param bits1 缓冲区 1
 @param bits2 缓冲区 2
 @param bitsx 计算结果
 @param size 每个缓冲区位个位
 */
void bit_xor(const unsigned char *bits1, const unsigned char *bits2, unsigned char *bitsx, int size);


/**
 轮转缓冲区 bits（含 size 位），将位值向左移 count 位 -　O(nβ) β 为每个缓冲区中位的个数，n 为要轮转到左边的位数
 @param bits 缓冲区
 @param size 缓冲区位个位
 @param count 左移位数
 */
void bit_rot_left(unsigned char *bits, int size, int count);


void bitree_init(BiTree *tree, void (*destroy)(void *data))
{
  /// 初始化二叉树
  tree->size = 0;
  tree->destroy = destroy;
  tree->root = NULL;

  return;
}


void bitree_destroy(BiTree *tree)
{
  /// 删除所有树的结点
  bitree_rem_left(tree, NULL);

  /// 清理二叉树数据结构
  memset(tree, 0, sizeof(BiTree));

  return;
}


int bitree_ins_left(BiTree *tree, BiTreeNode *node, const void *data)
{
  BiTreeNode    *new_node, **position;

  /// 确定插入结点的位置
  if (node == NULL) {

    /// 只要树为空才允许将结点作为根节点（node 为 NULL）
    if (bitree_size(tree) > 0) return -1;

    position = &tree->root;

  } else {

    /// 只有指定结点的左结点为空才允许插入
    if (bitree_left(node) != NULL) return -1;

    position = &node->left;

  }

  /// 初始化结点存储空间
  if ((new_node = (BiTreeNode *)malloc(sizeof(BiTreeNode))) == NULL) return -1;

  /// 将结点插入到树中
  new_node->data = (void *)data;
  new_node->left = NULL;
  new_node->right = NULL;
  *position = new_node;

  /// 更新树的 size
  tree->size++;

  return 0;
}


int bitree_ins_right(BiTree *tree, BiTreeNode *node, const void *data)
{
  BiTreeNode    *new_node, **position;

  /// 确定插入结点的位置
  if (node == NULL) {

    /// 只要树为空才允许将结点作为根节点（node 为 NULL）
    if (bitree_size(tree) > 0) return -1;

    position = &tree->root;

  } else {

    /// 只有指定结点的右结点为空才允许插入
    if (bitree_right(node) != NULL) return -1;

    position = &node->right;

  }

  /// 初始化结点存储空间
  if ((new_node = (BiTreeNode *)malloc(sizeof(BiTreeNode))) == NULL) return -1;

  /// 将结点插入到树中
  new_node->data = (void *)data;
  new_node->left = NULL;
  new_node->right = NULL;
  *position = new_node;

  /// 更新树的 size
  tree->size++;

  return 0;
}


void bitree_rem_left(BiTree *tree, BiTreeNode *node)
{
  BiTreeNode    **position;

  /// 不允许在空树中执行移除
  if (bitree_size(tree) == 0) return;

  /// 确定移除结点的位置
  if (node == NULL) {
    position = &tree->root;
  } else {
    position = &node->left;
  }

  /// 移除结点（按照后序遍历从参数 node 的左子结点开始依次移除）
  if (*position != NULL) {

    bitree_rem_left(tree, *position);
    bitree_rem_right(tree, *position);

    if (tree->destroy != NULL) {
      /// 执行用户指定的 destroy 函数
      tree->destroy((*position)->data);
    }

    free(*position);
    *position = NULL;

    /// 更新树的 size
    tree->size--;

  }

  return;
}


void bitree_rem_right(BiTree *tree, BiTreeNode *node)
{
  BiTreeNode    **position;

  /// 不允许在空树中执行移除
  if (bitree_size(tree) == 0) return;

  /// 确定移除结点的位置
  if (node == NULL) {
    position = &tree->root;
  } else {
    position = &node->right;
  }

  /// 移除结点（按照后序遍历从参数 node 的左子结点开始依次移除）
  if (*position != NULL) {

    bitree_rem_left(tree, *position);
    bitree_rem_right(tree, *position);

    if (tree->destroy != NULL) {
      /// 执行用户指定的 destroy 函数
      tree->destroy((*position)->data);
    }

    free(*position);
    *position = NULL;

    /// 更新树的 size
    tree->size--;

  }

  return;
}


int bitree_merge(BiTree *merge, BiTree *left, BiTree *right, const void *data)
{
  /// 初始化新的树 merge
  bitree_init(merge, left->destroy);

  /// 将 data 放入新树的根节点
  if (bitree_ins_left(merge, NULL, data) != 0) {

    bitree_destroy(merge);
    return -1;
  }

  /// 将两棵树合并到新树
  bitree_root(merge)->left = bitree_root(left);
  bitree_root(merge)->right = bitree_root(right);

  /// 设置新树的 size
  merge->size = merge->size + bitree_size(left) + bitree_size(right);

  /// 解除原来树中的结点关系并把 size 置为 0
  left->root = NULL;
  left->size = 0;
  right->root = NULL;
  right->size = 0;

  return 0;
}



typedef struct HuffNode_
{
  unsigned char   symbol;
  int             freq;

} HuffNode;


/**
 霍夫曼编码表
 */
typedef struct HuffCode_
{
  unsigned char     used;
  unsigned short    code;
  unsigned char     size;

} HuffCode;




typedef struct BiTree_
{
  int         size;

  int         (*compare)(const void *key1, const void *key2);
  void        (*destroy)(void *data);

  BiTreeNode  *root;

} BiTree;


/**
 初始化由参数 tree 所指定二叉树 - O(1)
 @param tree 二叉树
 @param destroy 成员析构函数（free...）
 */
void bitree_init(BiTree *tree, void (*destroy)(void *data));


/**
 销毁由参数 tree 所指定二叉树 - O(n) n 为结点个数
 @param tree 二叉树
 */
void bitree_destroy(BiTree *tree);


/**
 在 tree 所指定二叉树中插入一个 node 所指定结点的左子结点 - O(1)
 @param tree 二叉树
 @param node 指定的结点
 @param data 结点数据
 @return 插入成功返回0；否则返回-1
 */
int bitree_ins_left(BiTree *tree, BiTreeNode *node, const void *data);


/**
 在 tree 所指定二叉树中插入一个 node 所指定结点的右子结点 - O(1)
 @param tree 二叉树
 @param node 指定的结点
 @param data 结点数据
 @return 插入成功返回0；否则返回-1
 */
int bitree_ins_right(BiTree *tree, BiTreeNode *node, const void *data);


/**
 移除由 tree 指定二叉树中 node 的左子结点为根的子树  - O(m) m 为子树结点个数
 @param tree 二叉树
 @param node 指定结点
 */
void bitree_rem_left(BiTree *tree, BiTreeNode *node);


/**
 移除由 tree 指定二叉树中 node 的右子结点为根的子树  - O(m) m 为子树结点个数
 @param tree 二叉树
 @param node 指定结点
 */
void bitree_rem_right(BiTree *tree, BiTreeNode *node);


/**
 将 left 和 right 所指定的两棵二叉树合并为单棵二叉树 - O(1)
 @param merge 合并后的树
 @param left 合并后左子树
 @param right 合并后右子树
 @param data 新树的根节点数据
 @return 合并成功，返回0；否则返回-1
 */
int bitree_merge(BiTree *merge, BiTree *left, BiTree *right, const void *data);


/**
 由参数 tree 所指定二叉树中的结点个数 - O(1)
 @param tree 二叉树
 @return 结点个数
 */
#define bitree_size(tree) ((tree)->size)


/**
 返回由参数 tree 所指定二叉树的根结点 - O(1)
 @param tree 二叉树
 @return 根结点
 */
#define bitree_root(tree) ((tree)->root)


/**
 判断由参数 node 所标识结点是否为二叉树中某个分支的结束 - O(1)
 @param node 待判断结点
 @return 分支结束则返回1；否则返回0
 */
#define bitree_is_eob(node) ((node) == NULL)


/**
 判断由参数 node 所指定结点是否为二叉树中的叶子结点 - O(1)
 @param node 待判断结点
 @return 叶子结点返回1；否则返回0
 */
#define bitree_is_leaf(node) ((node)->left == NULL && (node)->right == NULL)


/**
 返回由参数 node 所指定结点中存储的数据 - O(1)
 @param node 指定结点
 @return 结点中存储的数据
 */
#define bitree_data(node) ((node)->data)


/**
 返回由参数 node 所指定结点的左子结点 - O(1)
 @param node 指定结点
 @return 指定结点的左子结点
 */
#define bitree_left(node) ((node)->left)


/**
 返回由参数 node 所指定结点的右子结点 - O(1)

 @param node 指定结点
 @return 指定结点的右子结点
 */
#define bitree_right(node) ((node)->right)



/**
 堆
 */
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


static int compare_freq(const void *tree1, const void *tree2)
{
  HuffNode    *root1, *root2;

  /// 比较两棵已经排序的二叉树树根节点

  root1 = (HuffNode *)bitree_data(bitree_root((const BiTree *)tree1));
  root2 = (HuffNode *)bitree_data(bitree_root((const BiTree *)tree2));

  if (root1->freq < root2->freq) return 1;
  if (root1->freq > root2->freq) return -1;
  return 0;
}


/**
 销毁霍夫曼树
 @param tree 霍夫曼树
 */
static void destroy_tree(void *tree)
{
  /// 销毁并回收一棵二叉树空间
  bitree_destroy(tree);
  free(tree);

  return;
}


/**
 通过字节频率建立霍夫曼树
 @param freqs 符号频率数组
 @param tree 构建后的霍夫曼树
 @return 成功返回 0, 否则返回 -1
 */
static int build_tree(int *freqs, BiTree **tree) {

  BiTree      *init, *merge, *left, *right;
  PQueue      pqueue;
  HuffNode    *data;
  int         size, c;

  /// 初始化二叉树优先队列

  *tree = NULL;

  pqueue_init(&pqueue, compare_freq, destroy_tree);

  for (c = 0; c <= UCHAR_MAX; c++) {

    if (freqs[c] != 0) {

      /// 创建二叉树并设置当前符号和频率

      if ((init = (BiTree *)malloc(sizeof(BiTree))) == NULL) {

        pqueue_destroy(&pqueue);
        return -1;
      }

      bitree_init(init, free);

      if ((data = (HuffNode *)malloc(sizeof(HuffNode))) == NULL) {

        pqueue_destroy(&pqueue);
        return -1;
      }

      data->symbol = c;
      data->freq = freqs[c];

      if (bitree_ins_left(init, NULL, data) != 0) {

        free(data);
        bitree_destroy(init);
        free(init);
        pqueue_destroy(&pqueue);
        return -1;
      }

      /// 插入二叉树到优先队列

      if (pqueue_insert(&pqueue, init) != 0) {

        bitree_destroy(init);
        free(init);
        pqueue_destroy(&pqueue);
        return -1;
      }
    }
  }

  /// 通过合并优先队列中的二叉树构建霍夫曼树

  size = pqueue_size(&pqueue);

  for (c = 1; c <= size - 1; c++) {

    /// 创建合并后树的空间

    if ((merge = (BiTree *)malloc(sizeof(BiTree))) == NULL) {

      pqueue_destroy(&pqueue);
      return -1;

    }

    /// 提取出两个根节点最小的两棵二叉树

    if (pqueue_extract(&pqueue, (void **)&left) != 0) {

      pqueue_destroy(&pqueue);
      free(merge);
      return -1;
    }

    if (pqueue_extract(&pqueue, (void **)&right) != 0) {

      pqueue_destroy(&pqueue);
      free(merge);
      return -1;
    }

    /// 创建合并后根节点的数据空间

    if ((data = (HuffNode *)malloc(sizeof(HuffNode))) == NULL) {

      pqueue_destroy(&pqueue);
      free(merge);
      return -1;
    }

    memset(data, 0, sizeof(HuffNode));

    /// 计算已经合并二叉树根节点的频率值（求和子节点）

    data->freq = ((HuffNode *)bitree_data(bitree_root(left)))->freq +
                 ((HuffNode *)bitree_data(bitree_root(right)))->freq;

    /// 合并两棵树

    if (bitree_merge(merge, left, right, data) != 0) {

      pqueue_destroy(&pqueue);
      free(merge);
      return -1;
    }

    /// 将合并的二叉树插入回优先队列并释放相关的空间

    if (pqueue_insert(&pqueue, merge) != 0) {

      pqueue_destroy(&pqueue);
      bitree_destroy(merge);
      free(merge);
      return -1;
    }

    free(left);
    free(right);
  }

  /// 优先队列中剩余的最后一棵二叉树就是霍夫曼树

  if (pqueue_extract(&pqueue, (void **)tree) != 0) {

    pqueue_destroy(&pqueue);
    return -1;

  } else {

    pqueue_destroy(&pqueue);
  }

  return 0;
}


/**
 建立霍夫曼编码表
 @param node 霍夫曼树结点
 @param code 当前生成的霍夫曼编码
 @param size 编码的位数
 @param table 霍夫曼编码结果
 */
static void build_table(BiTreeNode *node, unsigned short code, unsigned char size, HuffCode *table) {

  if (!bitree_is_eob(node)) {

    if (!bitree_is_eob(bitree_left(node))) {

      /// 向左移动并在编码末尾追加 0
      build_table(bitree_left(node), code << 1, size + 1, table);
    }

    if (!bitree_is_eob(bitree_right(node))) {

      /// 向右移动并在编码末尾追加 1
      build_table(bitree_right(node), (code << 1) | 0x0001, size + 1, table);
    }

    if (bitree_is_eob(bitree_left(node))&&bitree_is_eob(bitree_right(node))) {

      /// 确保当前编码是以大端字节格式存放
      code = htons(code);

      /// 将当前符号编码插入叶子节点

      table[((HuffNode *)bitree_data(node))->symbol].used = 1;
      table[((HuffNode *)bitree_data(node))->symbol].code = code;
      table[((HuffNode *)bitree_data(node))->symbol].size = size;
    }
  }

  return;
}


#pragma mark - Public


int huffman_compress(const unsigned char *original, unsigned char **compressed, int size)
{
  BiTree          *tree;
  HuffCode        table[UCHAR_MAX + 1];
  int             freqs[UCHAR_MAX + 1], max, scale, hsize, ipos, opos, cpos, c, i;
  unsigned char   *comp, *temp;

  /// 初始化最初的压缩结果为空
  *compressed = NULL;

  /// 获取原始数据中每个符号的频率

  for (c = 0; c <= UCHAR_MAX; c++) {
    freqs[c] = 0;
  }

  ipos = 0;

  if (size > 0) {

    while (ipos < size) {

      freqs[original[ipos]]++;
      ipos++;
    }
  }

  /// 缩放频率以适应一个 byte 大小（可以只用一个字节来表示）

  max = UCHAR_MAX;

  for (c = 0; c <= UCHAR_MAX; c++) {

    if (freqs[c] > max) {
      max = freqs[c];
    }
  }

  for (c = 0; c <= UCHAR_MAX; c++) {

    scale = (int)(freqs[c] / ((double)max / (double)UCHAR_MAX));

    if (scale == 0 && freqs[c] != 0) {
      /// 确保当任何非 0 频率值其缩减为小于 1 时，最终应该将其设为 1 而不是 0
      freqs[c] = 1;
    } else {
      freqs[c] = scale;
    }
  }

  /// 构建霍夫曼树和霍夫曼编码表

  if (build_tree(freqs, &tree) != 0) return -1;

  for (c = 0; c <= UCHAR_MAX; c++) {
    memset(&table[c], 0, sizeof(HuffCode));
  }

  build_table(bitree_root(tree), 0x0000, 0, table);

  bitree_destroy(tree);
  free(tree);

  /// 写入头部信息

  hsize = sizeof(int) + (UCHAR_MAX + 1);

  if ((comp = (unsigned char *)malloc(hsize)) == NULL) return -1;

  memcpy(comp, &size, sizeof(int));

  for (c = 0; c <= UCHAR_MAX; c++) {
    comp[sizeof(int) + c] = (unsigned char)freqs[c];
  }

  /// 压缩数据

  ipos = 0;
  opos = hsize * 8;

  while (ipos < size) {

    /// 获取原始数据中的下一个符号
    c = original[ipos];

    /// 将当前符号的 code 写入压缩后数据

    for (i = 0; i < table[c].size; i++) {

      if (opos % 8 == 0) {

        /// 创建另外一个 byte 用于存放压缩数据
        if ((temp = (unsigned char *)realloc(comp,(opos / 8) + 1)) == NULL) {

          free(comp);
          return -1;
        }

        comp = temp;

      }

      cpos = (sizeof(short) * 8) - table[c].size + i;
      bit_set(comp, opos, bit_get((unsigned char *)&table[c].code, cpos));
      opos++;

    }

    ipos++;
  }

  /// 将缓冲区指向已压缩数据
  *compressed = comp;

  /// 返回压缩后数据的长度
  return ((opos - 1) / 8) + 1;
}


int huffman_uncompress(const unsigned char *compressed, unsigned char **original)
{
  BiTree          *tree;
  BiTreeNode      *node;
  int             freqs[UCHAR_MAX + 1], hsize, size, ipos, opos, state, c;
  unsigned char   *orig, *temp;

  /// 初始化最初的解压结果为空
  *original = orig = NULL;

  /// 获取压缩数据中的头部信息

  hsize = sizeof(int) + (UCHAR_MAX + 1);
  memcpy(&size, compressed, sizeof(int));

  for (c = 0; c <= UCHAR_MAX; c++) {
    freqs[c] = compressed[sizeof(int) + c];
  }

  /// 通过获取的头部信息构建压缩数据时用的霍夫曼树
  if (build_tree(freqs, &tree) != 0) return -1;

  /// 解压数据

  ipos = hsize * 8;
  opos = 0;
  node = bitree_root(tree);

  while (opos < size) {

    /// 获取压缩数据中的下一位
    state = bit_get(compressed, ipos);
    ipos++;

    if (state == 0) {

      /// 向左移动

      if (bitree_is_eob(node) || bitree_is_eob(bitree_left(node))) {

        bitree_destroy(tree);
        free(tree);
        return -1;

      } else {
        node = bitree_left(node);
      }
    } else {

      /// 向右移动

      if (bitree_is_eob(node) || bitree_is_eob(bitree_right(node))) {

        bitree_destroy(tree);
        free(tree);
        return -1;
      } else {
        node = bitree_right(node);
      }
    }

    if (bitree_is_eob(bitree_left(node))&&bitree_is_eob(bitree_right(node))) {

      /// 将叶子节点中的符号写回解压数据

      if (opos > 0) {

        if ((temp = (unsigned char *)realloc(orig, opos + 1)) == NULL) {

          bitree_destroy(tree);
          free(tree);
          free(orig);
          return -1;
        }

        orig = temp;

      } else {

        if ((orig = (unsigned char *)malloc(1)) == NULL) {

          bitree_destroy(tree);
          free(tree);
          return -1;
        }
      }

      orig[opos] = ((HuffNode *)bitree_data(node))->symbol;
      opos++;

      /// 移回树的根节点
      node = bitree_root(tree);
    }
  }

  bitree_destroy(tree);
  free(tree);

  /// 将缓冲区指向已解压数据
  *original = orig;

  /// 返回解压后数据大小
  return opos;
}

