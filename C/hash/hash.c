#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define   TBLSIZ    11


/**
 链表结点
 */
typedef struct ListElmt_
{
  void              *data;
  struct ListElmt_  *next;

} ListElmt;


/**
 链表
 */
typedef struct List_
{
  int         size;
  int         (*match)(const void *key1, const void *key2);
  void        (*destroy)(void *data);
  ListElmt    *head;
  ListElmt    *tail;

} List;


/**
 初始化指定的链表 list - O(1)
 @param list 链表
 @param destroy 成员析构函数（free...）
 */
void list_init(List *list, void (*destroy)(void *data));


/**
 销毁指定的链表 list - O(n)
 @param list 链表
 */
void list_destroy(List *list);


/**
 在指定链表 list 中 element 后面插入一个新元素 - O(1)
 @param list 指定的链表
 @param element 新元素，如果为 NULL 则插入头部
 @param data 元素数据
 @return 成功返回 1，否则返回 -1
 */
int list_ins_next(List *list, ListElmt *element, const void *data);


/**
 在指定链表 list 中移除 element 后的元素 - O(1)
 @param list 指定的链表
 @param element 待移除元素前的元素，如果为 NULL 则移除头部
 @param data 已移除元素的存储数据
 @return 成功返回 0，否则返回 -1
 */
int list_rem_next(List *list, ListElmt *element, void **data);


/**
 获取指定链表 list 的长度 - O(1)
 @param list 指定的链表
 @return 链表中元素的个数
 */
#define list_size(list) ((list)->size)


/**
 获取指定链表 list 的头元素指针 - O(1)

 @param list 指定的链表
 @return 链表的头元素指针
 */
#define list_head(list) ((list)->head)


/**
 获取指定链表 list 的尾元素指针 - O(1)

 @param list 指定的链表
 @return 链表的尾元素指针
 */
#define list_tail(list) ((list)->tail)



/**
 判断元素 element 是否为指定链表 list 的头节点 - O(1)
 @param list 指定的链表
 @param element 待判断的元素
 @return 是返回 1，否则返回 0
 */
#define list_is_head(list, element) ((element) == (list)->head ? 1 : 0)


/**
 判断元素 element 是否为指定链表 list 的尾节点 - O(1)

 @param list 指定的链表
 @param element 待判断的元素
 @return 是返回 1，否则返回 0
 */
#define list_is_tail(element) ((element)->next == NULL ? 1 : 0)


/**
 获取指定元素 element 中保存的数据 - O(1)
 @param element 指定的元素
 @return 结点保存的数据
 */
#define list_data(element) ((element)->data)


/**
 获取指定元素 element 中保存的下一个节点 - O(1)

 @param element 指定的元素
 @return 结点的下一个节点
 省时间少打一个字儿
 */
#define list_next(element) ((element)->next)






void list_init(List *list, void (*destroy)(void *data))
{
  /// 初始化链表
  list->size = 0;
  list->destroy = destroy;
  list->head = NULL;
  list->tail = NULL;

  return;
}


void list_destroy(List *list)
{
  void *data;

  /// 删除每一个元素
  while (list_size(list) > 0) {
    if (list_rem_next(list, NULL, (void **)&data) == 0 && list->destroy != NULL) {
      /// 调用用户定义的 destroy 方法销毁动态创建的数据,把数据去掉，地址&data不管
      list->destroy(data);
    }
  }

  /// 清理链表结构体数据
  memset(list, 0, sizeof(List));

  return;
}


int list_ins_next(List *list, ListElmt *element, const void *data)
{
  ListElmt *new_element;

  /// 分配元素需要的空间
  if ((new_element = (ListElmt *)malloc(sizeof(ListElmt))) == NULL) return -1;

  /// 插入元素到链表
  new_element->data = (void *)data;

  if (element == NULL) {

    /// 处理插入到头部的情况

    if (list_size(list) == 0) {
      list->tail = new_element;
    }

    new_element->next = list->head;  ///往回指
    list->head = new_element;

  } else {

    /// 处理其他情况

    if (element->next == NULL) {
      list->tail = new_element;
    }

    new_element->next = element->next;
    element->next = new_element;

  }

  /// 更新链表的 size
  list->size++;

  return 0;
}


int list_rem_next(List *list, ListElmt *element, void **data)
{
  ListElmt *old_element;

  /// 禁止删除空链表的数据
  if (list_size(list) == 0) return -1;

  /// 从链表中删除元素
  if (element == NULL) {

    /// 处理删除头部元素

    *data = list->head->data;
    old_element = list->head;
    list->head = list->head->next;

    if (list_size(list) == 1) {
      list->tail = NULL;
    }

  } else {

    /// 处理其他情况

    if (element->next == NULL) return -1;

    *data = element->next->data;
    old_element = element->next;
    element->next = element->next->next;

    if (element->next == NULL) {
      list->tail = element;//tail指向最后一块了，如果这个时候element变成最后一块了，要移动  
    }

  }

  /// 清理旧结点元素的,让所有指向清理结点的指针都指向NULL，统一free，直接free->next不行，不能所有都估计 
  free(old_element);

  /// 更新链表的 size
  list->size--;

  return 0;
}


/**
 链式哈希表
 */
typedef struct CHTbl_
{
  int     buckets;

  int     (*h)(const void *key);
  int     (*match)(const void *key1, const void *key2);
  void    (*destroy)(void *data);

  int     size;
  List    *table;

} CHTbl;


/**
 初始化 htbl 指定的链式哈希表 - O(m)，m 是哈希表中“桶”的个数
 @param htbl 哈希表
 @param buckets 所分配的“桶”的个数
 @param h 函数指针，用户定义的哈希函数
 @param match 函数指针，用于判断两个成员是否相匹配
 @param destroy 成员析构函数（free...）
 @return 表初始化成功，返回0；否则返回-1
 */
int chtbl_init(CHTbl *htbl, int buckets,
               int (*h)(const void *key),
               int (*match)(const void *key1, const void *key2),
               void (*destroy)(void *data));


/**
 销毁 htbl 指定的链式哈希表 - O(m)
 @param htbl 哈希表
 */
void chtbl_destroy(CHTbl *htbl);


/**
 向 htbl 指定的链式哈希表中插入一个元素 - O(1)
 @param htbl 哈希表
 @param data 待插入元素
 @return 插入成功，返回0；已包含此元素，返回1；否则，返回-1
 */
int chtbl_insert(CHTbl *htbl, const void *data);


/**
 从 htbl 指定的链式哈希表中删除与 data 匹配的元素 - O(1)
 @param htbl 哈希表
 @param data 待删除元素
 @return 删除成功，返回0；否则，返回-1
 */
int chtbl_remove(CHTbl *htbl, void **data);


/**
 判断由参数 htbl 指定的链式哈希表中查找是否有与 data 相匹配的元素 - O(1)
 @param htbl 哈希表
 @param data 待查找元素
 @return 找到元素，返回0；否则，返回-1
 */
int chtbl_lookup(const CHTbl *htbl, void **data);


/**
 返回由参数 htbl 指定的链式哈希表中元素的个数 - O(1)
 @param htbl 哈希表
 @return 哈希表中元素的个数
 */
#define chtbl_size(htbl) ((htbl)->size)




static int match_char(const void *char1, const void *char2)
{
  /// 判断两个字符是否相等, 必须得用字符比较char
  return (*(const char *)char1 == *(const char *)char2);
}
//感觉用static就是没法迭代的意思，return里面不能再迭代了，如果迭代，只模一次，
static int h_char(const void *key) {
  /// 定义简单 hash 分配函数
  return *(const char *)key % TBLSIZ;
  //return *(const char *)key % 100; //也OK 的！这里只是随机打散
}

static void print_table(const CHTbl *htbl)
{
  ListElmt    *element;
  int         i;

  /// 打印 hash 表
  fprintf(stdout, "-> Table size is %d\n", chtbl_size(htbl));

  for (i = 0; i < TBLSIZ; i++) {

    fprintf(stdout, "--> Bucket[%03d]=", i);
    //->本身就是*的意思了，(list)->head必须得是指针结构才能指进去
    for (element = list_head(&htbl->table[i]); element != NULL; element = list_next(element)) {

      fprintf(stdout, " %c", *(char *)list_data(element));
    }

    fprintf(stdout, "\n");
  }

  return;
}




int chtbl_init(CHTbl *htbl, int buckets,
               int (*h)(const void *key),
               int (*match)(const void *key1, const void *key2),
               void (*destroy)(void *data))
{

  int     i;

  /// 创建 hash 表所需空间 数组定义方法
  if ((htbl->table = (List *)malloc(buckets * sizeof(List))) == NULL) return -1;

  /// 初始化 buckets
  htbl->buckets = buckets;

  for (i = 0; i < htbl->buckets; i++) {
    list_init(&htbl->table[i], destroy);
  }

  /// 封装函数进 hash 表
  htbl->h = h;
  htbl->match = match;
  htbl->destroy = destroy;

  /// 初始化表大小为 0
  htbl->size = 0;

  return 0;
}


void chtbl_destroy(CHTbl *htbl)
{

  int     i;

  /// 删除 buckets
  for (i = 0; i < htbl->buckets; i++) {
    list_destroy(&htbl->table[i]); //htbl->table[i]=*list ,&htbl->table[i]=list, 因为table本身不是指针，要用地址
  }

  /// 清理 hash 表空间  不用&因为table本身就是指针
  free(htbl->table);
  /// 清理 hash 表结构体数据
  memset(htbl, 0, sizeof(CHTbl));

  return;
}


int chtbl_insert(CHTbl *htbl, const void *data)
{

  void      *temp;
  int     bucket, retval;

  /// 如果元素已经存在返回 1
  temp = (void *)data;

  if (chtbl_lookup(htbl, &temp) == 0) return 1;

  /// 计算 hash，第二次模htbl->buckets保证了bucket在TBLSIZ范围里面，第一次模可以取别的数
  bucket = htbl->h(data) % htbl->buckets;

// printf("bucket=%03d data in char =%c  data in decimal=%03d address is=%03d hash(data)=%03d\n",bucket,*(char *)data,*(int*)data,(int*)data, htbl->h(data));
//bucket=006 data in char =u  data in decimal=117 address is=14380232 hash(data)=017
//输入的是117，mod11=17  17mod11=6=bucket，这里对应的h_char%100
  /// 插入到相应的 bucket
  if ((retval = list_ins_next(&htbl->table[bucket], NULL, data)) == 0) {
    htbl->size++;
  }

  return retval;
}


int chtbl_remove(CHTbl *htbl, void **data)
{

  ListElmt      *element, *prev;
  int           bucket;

  /// 计算 hash
  bucket = htbl->h(*data) % htbl->buckets;

  /// 在 bucket 中查找数据
  prev = NULL;

  for (element = list_head(&htbl->table[bucket]); element != NULL; element = list_next(element)) {

    if (htbl->match(*data, list_data(element))) {

      /// 从 bucket 中移除找到的元素
      if (list_rem_next(&htbl->table[bucket], prev, data) != 0) return -1;

      htbl->size--;
      return 0;

    }
    prev = element;

  }

  /// 如果没找到返回 -1
  return -1;
}


int chtbl_lookup(const CHTbl *htbl, void **data) {

  ListElmt      *element;
  int           bucket;

  /// 计算 hash
  bucket = htbl->h(*data) % htbl->buckets;

  /// 在 bucket 中查找数据  感觉这里用&的意思是， *data，data指向一个数。别人指向data那么用&data，指向list的指针，list和 &data其实是一个作用，都是指向 data，但是如果
  ///但是如果 *data，这时候是 data指向的另外一个地址，如果是&data是指向data的地址，所以上面会等价
  for (element = list_head(&htbl->table[bucket]); element != NULL; element = list_next(element)) {

    if (htbl->match(*data, list_data(element))) {

      /// 返回找到的数据
      *data = list_data(element);
      return 0;

    }
  }

  /// 如果没找到返回 -1
  return -1;
}

int main(int argc, char **argv)
{

  CHTbl     htbl;
  char      *data, c;
  int       retval, i;

  /// 初始化链式哈希表
  if (chtbl_init(&htbl, TBLSIZ, h_char, match_char, free) != 0) return 1;

  /// 执行哈希表操作
  for (i = 0; i < TBLSIZ; i++) {
      //realloc也可以malloc，只是，realloc有其他扩展功能，malloc就全清零了，反复用指针要清零
    if ((data = (char *)malloc(sizeof(char))) == NULL) return 1;
    //*不停更新，要重新分配，如果是不带*的比如element=list_next(element) 就不用重新分配
    *data = ((5 + (i * 6)) % 23) + 'A';//TBLSIZ不一样，保证22个不重复，重复就打回去了‘
//*data = ((0 + (i * 1)) % 23) + 'A';// 不能随机出新字母是按照顺序出的，5,6奇偶保证打散的不规律？
// if (chtbl_lookup(htbl, &temp) == 0) return 1; insert里面有这句话所以 用这个取模保证不重复，如果
//Insert里面用别的方法处理重复就不用这边考虑重复的问题了，*data是浅拷贝，data直接拷贝地址是深拷贝
//浅拷贝如果不重新分配就有拷贝不进去的危险    
    if (chtbl_insert(&htbl, data) != 0) return 1;

    print_table(&htbl);

  }

  for (i = 0; i < TBLSIZ; i++) {

    if ((data = (char *)malloc(sizeof(char))) == NULL) return 1;

    *data = ((3 + (i * 4)) % 23) + 'a';

    if (chtbl_insert(&htbl, data) != 0) return 1;

    print_table(&htbl);

  }

  if ((data = (char *)malloc(sizeof(char))) == NULL) return 1;

  *data = 'd';

  if ((retval = chtbl_insert(&htbl, data)) != 0) free(data);

  fprintf(stdout, "Trying to insert d again...Value=%d (1=OK)\n", retval);

  if ((data = (char *)malloc(sizeof(char))) == NULL) return 1;

  *data = 'G';

  if ((retval = chtbl_insert(&htbl, data)) != 0) free(data);

  fprintf(stdout, "Trying to insert G again...Value=%d (1=OK)\n", retval);

  fprintf(stdout, "Removing d, G, and S\n");

  c = 'd';
  data = &c;

  if (chtbl_remove(&htbl, (void **)&data) == 0) free(data);

  c = 'G';
  data = &c;

  if (chtbl_remove(&htbl, (void **)&data) == 0) free(data);

  c = 'S';
  data = &c;

  if (chtbl_remove(&htbl, (void **)&data) == 0) free(data);

  print_table(&htbl);

  if ((data = (char *)malloc(sizeof(char))) == NULL) return 1;

  *data = 'd';

  if ((retval = chtbl_insert(&htbl, data)) != 0) free(data);

  fprintf(stdout, "Trying to insert d again...Value=%d (0=OK)\n", retval);

  if ((data = (char *)malloc(sizeof(char))) == NULL) return 1;

  *data = 'G';

  if ((retval = chtbl_insert(&htbl, data)) != 0) free(data);

  fprintf(stdout, "Trying to insert G again...Value=%d (0=OK)\n", retval);

  print_table(&htbl);

  fprintf(stdout, "Inserting X and Y\n");

  if ((data = (char *)malloc(sizeof(char))) == NULL) return 1;

  *data = 'X';

  if (chtbl_insert(&htbl, data) != 0) return 1;

  if ((data = (char *)malloc(sizeof(char))) == NULL) return 1;

  *data = 'Y';

  if (chtbl_insert(&htbl, data) != 0) return 1;

  print_table(&htbl);

  c = 'X';
  data = &c;

  if (chtbl_lookup(&htbl, (void **)&data) == 0) {
       fprintf(stdout, "Found an occurrence of %c\n",*(char*)data);
  } else {
      fprintf(stdout, "Did not find an occurrence of %c\n",*(char*)data);
  }

  c = 'Z';
  data = &c;

  if (chtbl_lookup(&htbl, (void **)&data) == 0) {
    fprintf(stdout, "Found an occurrence of %c\n",*(char*)data);
  } else {
    fprintf(stdout, "Did not find an occurrence of %c\n",*(char*)data);
  }

  /// 清理 hash 表数据
  fprintf(stdout, "Destroying the hash table\n");
  chtbl_destroy(&htbl);

  return 0;

}

/*


typedef struct  _CHTbl
{
   int size;
   int buckets;
   List *table;

   int(*match)(const void *key1,const void *key2);
   int(*h)(const void *data);
   void(*destroy)(void *data);
}CHTbl;

int init_htbl(CHTbl *htbl,int bucket,
                int(*h)(const void *data),int(*match)(const void *key1,const void *key2),
                 void(*destroy)(void *data))
{
    int i;
    if((htbl->table=(List*)malloc(bucket*sizeof(List)))==NULL)
    {
        return 1;
    }
        for(i=0;i<TBLSIZ;i++)
        {
            list_init(&htbl->table[i], destroy);
        }

        htbl->size=0;
        htbl->buckets=bucket;
        htbl->match=match;
        htbl->h=h;
        htbl->destroy=destroy;

        return 0;

}

int h_char(const void *key)
{

    return(*(char*)key%TBLSIZ);
}


int match_char(const void *key1,const void *key2)
{

return(*(char*)key1==*(char*)key2);
}


void htbl_destroy(CHTbl *htbl)
{
    int i;
    if(htbl->destroy!=NULL)
    {
        for(i=0;i<TBLSIZ;i++)
        {
             list_destroy(&htbl->table[i]);
        }
    }
    free(htbl->table);

    memset(htbl,0,sizeof(CHTbl));

return ;
}

void print_htbl(CHTbl *htbl)
{
    int i;
    ListElm *element;
    printf("-->size of the hash table is %d\n",htbl->size);

    for(i=0;i<TBLSIZ;i++)
    {
        printf("the bucket[%03d] :",i);
        for(element=list_head(&htbl->table[i]);element!=NULL;element=list_next(element))
        {
            printf(" %c ",*(char *)element->data);
        }
        puts(" ");
    }


return ;

}

int htbl_lookup(const CHTbl *htbl,void *data)
{
    ListElm *element;
     int bucket=htbl->h(data)%htbl->buckets;

        for(element=list_head(&htbl->table[bucket]);element!=NULL;element=list_next(element))
        {
            //if(*(int*)element->data==*(int*)data)
            if (htbl->match(data, list_data(element)))
                {data=element->data;
                return 0;}


        }

        return -1;
}



int chtbl_insert(CHTbl *htbl,const void *data)
{
        ListElm *element;
        void      *temp;
        int retval=0;
          temp = (void *)data;

         if(htbl_lookup(htbl,temp)==0) return -1;

        int bucket=htbl->h(data) % htbl->buckets ;



        if((retval=(list_ins_next(&htbl->table[bucket],NULL,data)))==0)

       {
           htbl->size++;
       }

        return  retval;


}

int chtbl_rem(CHTbl *htbl, void *data)
{
    ListElm *element,*prev;
    int bucket;

    bucket=htbl->h(data)%htbl->buckets;

    if(htbl_lookup(htbl,data)!=0) return -1;
    prev = NULL;
    for(element=list_head(&htbl->table[bucket]);element!=NULL;element=list_next(element))
    {       //必须用字符比较
         if(*(char*)data==*(char*)element->data&&list_rem_next(&htbl->table[bucket],prev,&data)==0)

            {htbl->size--;
             return 0;

            }

         prev=element;

    }

return -1;

}

int main (int argc,char **argv)
{
    CHTbl htbl;
    char *data,c;
    int i,retval;

   if( init_htbl(&htbl,TBLSIZ,h_char,match_char,free)!=0) return -1;

   for(i=0;i<TBLSIZ;i++)
   {
       if ((data = (char *)malloc(sizeof(char))) == NULL) return 1;

      *data = ((5 + (i * 6)) % 23) + 'A';

       if(chtbl_insert(&htbl,data)!=0)

       {printf(" %d ======",chtbl_insert(&htbl,data));
           return -1;}

        print_htbl(&htbl);

   }


   for(i=0;i<TBLSIZ;i++)
   {
       if ((data = (char *)malloc(sizeof(char))) == NULL) return 1;

       *data = ((3 + (i * 4)) % 23) + 'a';

       if(chtbl_insert(&htbl,data)!=0) return 1;

        print_htbl(&htbl);

   }


  if ((data = (char *)malloc(sizeof(char))) == NULL) return 1;

  *data='d';

  if((retval=chtbl_insert(&htbl,data))!=0) free(data);

  fprintf(stdout,"insert d again value =%d\n",retval);


if ((data = (char *)malloc(sizeof(char))) == NULL) return 1;

  *data='G';
  if((retval=chtbl_insert(&htbl,data))!=0) free(data);

  fprintf(stdout,"insert G again value =%d\n",retval);


  fprintf(stdout, "Removing d, G, and S\n");

    c='d';
    data=&c;
    if(chtbl_rem(&htbl,(void*)data)==0) free(data);

     c='G';
    data=&c;
    if(chtbl_rem(&htbl,(void*)data)==0) free(data);

     c='S';
    data=&c;
    if(chtbl_rem(&htbl,(void*)data)==0) free(data);

         print_htbl(&htbl);

         if ((data = (char *)malloc(sizeof(char))) == NULL) return 1;

  *data = 'd';

  if ((retval = chtbl_insert(&htbl, data)) != 0) free(data);

  fprintf(stdout, "Trying to insert d again...Value=%d (0=OK)\n", retval);

  if ((data = (char *)malloc(sizeof(char))) == NULL) return 1;

  *data = 'G';

  if ((retval = chtbl_insert(&htbl, data)) != 0) free(data);

  fprintf(stdout, "Trying to insert G again...Value=%d (0=OK)\n", retval);

  print_htbl(&htbl);












        return 0;
}

*/