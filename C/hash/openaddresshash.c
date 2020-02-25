#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define            TBLSIZ               11
static char        vacated;

typedef struct OHTbl_
{
  int     positions;
  void    *vacated;

  int     (*h1)(const void *key);
  int     (*h2)(const void *key);
  int     (*match)(const void *key1, const void *key2);
  void    (*destroy)(void *data);

  int     size;
  void    **table;

} OHTbl;


/**
  初始化 htbl 指定的开地址哈希表 - O(m)，m 是哈希表中槽位的个数
 @param htbl 哈希表
 @param positions 槽位的个数
 @param h1 函数指针，用户定义的辅助哈希函数1
 @param h2 函数指针，用户定义的辅助哈希函数2
 @param match 函数指针，用于判断两个成员是否相匹配
 @param destroy 成员析构函数（free...）
 @return 初始化成功，返回0；否则返回-1
 */
int ohtbl_init(OHTbl *htbl, int positions,
               int (*h1)(const void *key),
               int (*h2)(const void *key),
               int (*match)(const void *key1, const void *key2),
               void (*destroy)(void *data));


/**
 销毁 htbl 指定的开地址哈希表 - O(m)

 @param htbl 哈希表
 */
void ohtbl_destroy(OHTbl *htbl);


/**
 向 htbl 指定的开地址哈希表中插入一个元素 - O(1)

 @param htbl 哈希表
 @param data 待插入元素
 @return 插入成功，返回0；已包含此元素，返回1；否则，返回-1
 */
int ohtbl_insert(OHTbl *htbl, const void *data);


/**
 从 htbl 指定的开地址哈希表中删除与 data 匹配的元素 - O(1)

 @param htbl 哈希表
 @param data 待删除元素
 @return 删除成功，返回0；否则，返回-1
 */
int ohtbl_remove(OHTbl *htbl, void **data);


/**
 判断由参数 htbl 指定的开地址哈希表中查找是否有与 data 相匹配的元素 - O(1)

 @param htbl 哈希表
 @param data 待查找元素
 @return 找到元素，返回0；否则，返回-1
 */
int ohtbl_lookup(const OHTbl *htbl, void **data);


/**
 返回由参数 htbl 指定的开地址哈希表中元素的个数 - O(1)

 @param htbl 哈希表
 @return 哈希表中元素的个数
 */
#define ohtbl_size(htbl) ((htbl)->size)




int ohtbl_init(OHTbl *htbl, int positions,
               int (*h1)(const void *key),
               int (*h2)(const void *key),
               int (*match)(const void *key1, const void *key2),
               void (*destroy)(void *data))
{
  int     i;

  if ((htbl->table = (void **)malloc(positions * sizeof(void *))) == NULL) return -1;

  /// 创建 hash 表所需空间
  htbl->positions = positions;

  for (i = 0; i < htbl->positions; i++) {
    htbl->table[i] = NULL;
  }

  /// 设置哨兵元素
  htbl->vacated = &vacated;

  /// 封装函数进 hash 表
  htbl->h1 = h1;
  htbl->h2 = h2;
  htbl->match = match;
  htbl->destroy = destroy;

  /// 初始化表大小为 0
  htbl->size = 0;

  return 0;
}


void ohtbl_destroy(OHTbl *htbl)
{
  int     i;

  if (htbl->destroy != NULL) {

    /// 调用用户定义 destroy 方法删除元素
    for (i = 0; i < htbl->positions; i++) {

      if (htbl->table[i] != NULL && htbl->table[i] != htbl->vacated) {

        htbl->destroy(htbl->table[i]);
      }
    }
  }

  /// 清理 hash 表空间
  free(htbl->table);

  /// 清理 hash 表结构体数据
  memset(htbl, 0, sizeof(OHTbl));

  return;
}


int ohtbl_insert(OHTbl *htbl, const void *data)
{
  void      *temp;
  int       position, i;

  /// 如果没有空间，返回 -1
  if (htbl->size == htbl->positions) return -1;

  /// 如果元素已经存在返回 1
  temp = (void *)data;
  if (ohtbl_lookup(htbl, &temp) == 0) return 1;

  /// 使用双重 hash 对元素计算 key
  for (i = 0; i < htbl->positions; i++) {

    position = (htbl->h1(data) + (i * htbl->h2(data))) % htbl->positions;

    if (htbl->table[position] == NULL || htbl->table[position] == htbl->vacated) {

      /// 将数据插入到表中
      htbl->table[position] = (void *)data;
      htbl->size++;
      return 0;
    }
  }

  /// 找不到合适的槽位返回 -1
  return -1;

}


int ohtbl_remove(OHTbl *htbl, void **data)
{
  int     position, i;

  /// 使用双重 hash 对元素计算 key
  for (i = 0; i < htbl->positions; i++) {

    position = (htbl->h1(*data) + (i * htbl->h2(*data))) % htbl->positions;

    /// 如果没找到返回 -1
    if (htbl->table[position] == NULL) return -1;

    if (htbl->table[position] == htbl->vacated) {

      /// 找到哨兵元素则继续
      continue;

    } else if (htbl->match(htbl->table[position], *data)) {

      /// 将找到的元素放入 data
      *data = htbl->table[position];
      htbl->table[position] = htbl->vacated;
      htbl->size--;
      return 0;

    }
  }

  /// 如果没找到返回 -1
  return -1;
}


int ohtbl_lookup(const OHTbl *htbl, void **data)
{
  int     position, i;

  /// 使用双重 hash 对元素计算 key
  for (i = 0; i < htbl->positions; i++) {

    position = (htbl->h1(*data) + (i * htbl->h2(*data))) % htbl->positions;

    if (htbl->table[position] == NULL) return -1;


    if (htbl->match(htbl->table[position], *data)) {

      /// 将找到的元素放入 data
      *data = htbl->table[position];
      return 0;

    }
  }

  /// 如果没找到返回 -1
  return -1;
}




static int match_char(const void *char1, const void *char2)
{
  /// 判断两个字符是否相等
  return (*(const char *)char1 == *(const char *)char2);
}


static int h1_char(const void *key)
{
  /// 定义简单 hash 分配函数 1
  return *(const char *)key % TBLSIZ;

}


static int h2_char(const void *key)
{
  /// 定义简单 hash 分配函数 1
  return 1 + (*(const char *)key % (TBLSIZ - 2));
}


static void print_table(const OHTbl *htbl)
{
  int     i;

  /// 打印 hash 表
  fprintf(stdout, "-> Table size is %d\n", ohtbl_size(htbl));

  for (i = 0; i < TBLSIZ; i++) {

    if (htbl->table[i] != NULL && htbl->table[i] != htbl->vacated) {

      fprintf(stdout, "--> Slot[%03d]=%c\n", i, *(char *)htbl->table[i]);

    } else {

      fprintf(stdout, "--> Slot[%03d]= \n", i);

    }
  }

  return;
}


int main(int argc, char **argv)
{
  OHTbl     htbl;
  char      *data, c;
  int       retval, i, j;

  /// 初始化开地址哈希表
  if (ohtbl_init(&htbl, TBLSIZ, h1_char, h2_char, match_char, free) != 0) return 1;

   /// 执行哈希表操作
  for (i = 0; i < 5; i++) {

    if ((data = (char *)malloc(sizeof(char))) == NULL) return 1;

    /// 模拟随机数据
    *data = ((8 + (i * 9)) % 23) + 'A';

    fprintf(stdout, "Hashing %c:", *data);

    for (j = 0; j < TBLSIZ; j++) {
      fprintf(stdout," %02d", (h1_char(data) + (j * h2_char(data))) % TBLSIZ);
    }

    fprintf(stdout, "\n");

    if (ohtbl_insert(&htbl, data) != 0) return 1;

    print_table(&htbl);
  }

  for (i = 0; i < 5; i++) {

    if ((data = (char *)malloc(sizeof(char))) == NULL) return 1;

    /// 模拟 hash 碰撞
    *data = ((8 + (i * 9)) % 13) + 'j';

    fprintf(stdout, "Hashing %c:", *data);

    for (j = 0; j < TBLSIZ; j++) {
      fprintf(stdout," %02d", (h1_char(data) + (j * h2_char(data))) % TBLSIZ);
    }

    fprintf(stdout, "\n");

    if (ohtbl_insert(&htbl, data) != 0) return 1;

    print_table(&htbl);
  }

  if ((data = (char *)malloc(sizeof(char))) == NULL) return 1;

  *data = 'R';

  if ((retval = ohtbl_insert(&htbl, data)) != 0) free(data);

  fprintf(stdout, "Trying to insert R again...Value=%d (1=OK)\n", retval);

  if ((data = (char *)malloc(sizeof(char))) == NULL) return 1;

  *data = 'n';

  if ((retval = ohtbl_insert(&htbl, data)) != 0) free(data);

  fprintf(stdout, "Trying to insert n again...Value=%d (1=OK)\n", retval);

  if ((data = (char *)malloc(sizeof(char))) == NULL) return 1;

  *data = 'o';

  if ((retval = ohtbl_insert(&htbl, data)) != 0) free(data);

  fprintf(stdout, "Trying to insert o again...Value=%d (1=OK)\n", retval);

  fprintf(stdout, "Removing R, n, and o\n");

  c = 'R';
  data = &c;

  if (ohtbl_remove(&htbl, (void **)&data) == 0) free(data);

  c = 'n';
  data = &c;

  if (ohtbl_remove(&htbl, (void **)&data) == 0) free(data);

  c = 'o';
  data = &c;

  if (ohtbl_remove(&htbl, (void **)&data) == 0) free(data);

  print_table(&htbl);

  if ((data = (char *)malloc(sizeof(char))) == NULL) return 1;

  *data = 'R';

  if ((retval = ohtbl_insert(&htbl, data)) != 0) free(data);

  fprintf(stdout, "Hashing %c:", *data);

  for (j = 0; j < TBLSIZ; j++) {
    fprintf(stdout, " %02d", (h1_char(data) + (j * h2_char(data))) % TBLSIZ);
  }

  fprintf(stdout, "\n");

  fprintf(stdout, "Trying to insert R again...Value=%d (0=OK)\n", retval);

  if ((data = (char *)malloc(sizeof(char))) == NULL) return 1;

  *data = 'n';

  if ((retval = ohtbl_insert(&htbl, data)) != 0) free(data);

  fprintf(stdout, "Hashing %c:", *data);

  for (j = 0; j < TBLSIZ; j++) {
    fprintf(stdout, " %02d", (h1_char(data) + (j * h2_char(data))) % TBLSIZ);
  }

  fprintf(stdout, "\n");

  fprintf(stdout, "Trying to insert n again...Value=%d (0=OK)\n", retval);

  if ((data = (char *)malloc(sizeof(char))) == NULL) return 1;

  *data = 'o';

  if ((retval = ohtbl_insert(&htbl, data)) != 0) free(data);

  fprintf(stdout, "Hashing %c:", *data);

  for (j = 0; j < TBLSIZ; j++) {
    fprintf(stdout, " %02d", (h1_char(data) + (j * h2_char(data))) % TBLSIZ);
  }

  fprintf(stdout, "\n");

  fprintf(stdout, "Trying to insert o again...Value=%d (0=OK)\n", retval);

  print_table(&htbl);

  fprintf(stdout, "Inserting X\n");

  if ((data = (char *)malloc(sizeof(char))) == NULL) return 1;

  *data = 'X';

  if (ohtbl_insert(&htbl, data) != 0) return 1;

  print_table(&htbl);

  if ((data = (char *)malloc(sizeof(char))) == NULL) return 1;

  *data = 'Y';

  if ((retval = ohtbl_insert(&htbl, data)) != 0) free(data);

  fprintf(stdout, "Trying to insert into a full table...Value=%d (-1=OK)\n", retval);

  c = 'o';
  data = &c;

  if (ohtbl_lookup(&htbl, (void **)&data) == 0) {
    fprintf(stdout, "Found an occurrence of o\n");
  } else {
    fprintf(stdout, "Did not find an occurrence of X\n");
  }

  c = 'Z';
  data = &c;

  if (ohtbl_lookup(&htbl, (void **)&data) == 0) {
    fprintf(stdout, "Found an occurrence of Z\n");
  } else {
    fprintf(stdout, "Did not find an occurrence of Z\n");
  }

  /// 清理 hash 表数据
  fprintf(stdout, "Destroying the hash table\n");
  ohtbl_destroy(&htbl);

  return 0;
}
