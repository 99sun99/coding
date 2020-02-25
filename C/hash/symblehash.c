#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define TBLSIZ 11

typedef struct ListElmt_
{
        int *data;

        struct ListElmt_ *next;

}ListElmt;

typedef struct List_
{
    int size;

    int (*match)(const void *key1,const void *key2);
    void (*destroy) (void *data);
     ListElmt *head;
     ListElmt *tail;
}List;


#define list_size(list)((list)->size)
#define list_head(list) ((list)->head)
#define list_tail(list) ((list)->tail)
#define list_is_head(list,element) ((element)==(list)->head ? 1 : 0)
#define list_is_tail(list,element) ((element)==(list)->tail ? 1 : 0)
#define list_data(list) ((list)->data)
#define list_next(element) ((element)->next)
#define  chtbl_size(htbl) ((htbl)->size)


void list_init(List *list,void(*destroy)(void *data))
{
        list->size=0;
        list->head=NULL;
        list->tail=NULL;
        list->destroy=destroy;

return;

}

void list_destroy(List *list)
{
    void *data;
    while(list_size(list)>0)
    {
        if(list->destroy!=NULL&&list_rem_next(list, NULL,(void**)&data)==0)
        {
            list->destroy(data);
        }
    }
memset(list,0,sizeof(List));

return;
}

int list_ins_next(List *list,ListElmt *element,const void *data)
{
    ListElmt *new_element;
    if((new_element=(ListElmt*)malloc(sizeof(ListElmt)))==NULL)
    {
        puts("error to allocate memory when list inserting");
        return -1;
    }

new_element->data=(void*)data;
if(element==NULL)
{
    if(list_size(list)==0)
    {
        list->tail=new_element;
    }
    new_element->next=list->head;
    list->head=new_element;

}else{
    if(element->next==NULL)
    {
        list->tail=new_element;
    }
    new_element->next=element->next;
    element->next=new_element;
   list->size++;
}
return 0;
}

int list_rem_next(List *list,ListElmt *element,void **data)
{
   ListElmt *old_element;
   if(list_size(list)==0)
   {
       puts("nothing to remove");
       return -1;
   }
    if(element==NULL)
    {
      *data=list->head->data;
      old_element=list->head;
      list->head=list->head->next;
      if(list_size(list)==1)
      {
          list->tail==NULL;
      }
    }else{
        if(element->next==NULL) return -1;
        *data=element->next->data;
        old_element=element->next;
        element->next=element->next->next;

        if(element->next==NULL)
        {
            list->tail=element;
        }
    }
   free(old_element);

    list->size--;
    return 0;
}


typedef enum Token_ {lexit, error, digit, other} Token;


/**
 根据输入流生成符号表
 @param istream 输入流
 @param symtbl 符号表
 @return 类型
 */
Token lex(const char *istream, CHTbl *symtbl);


static char *next_token(const char *istream)
{
  return NULL;
}


/**
 符号标记
 */
typedef struct
{
  char               *lexeme;
  Token              token;

} Symbol;





Token lex(const char *istream, CHTbl *symtbl)
{

  Token     token;
  Symbol    *symbol;
  int       length, retval, i;

  /// 创建符号表的空间
  if ((symbol = (Symbol *)malloc(sizeof(Symbol))) == NULL) return error;

  /// 对输入流进行分割
  if ((symbol->lexeme = next_token(istream)) == NULL) {

    /// 如果没有更多数据则返回
    free(symbol);
    return lexit;

  } else {

    /// 判断符号类型
    symbol->token = digit;
    length = (int)strlen(symbol->lexeme);

    for (i = 0; i < length; i++) {

      if (!isdigit(symbol->lexeme[i])) {
        symbol->token = other;
      }
    }

    memcpy(&token, &symbol->token, sizeof(Token));

    /// 插入到符号表
    if ((retval = chtbl_insert(symtbl, symbol)) < 0) {

      free(symbol);
      return error;

    } else if (retval == 1) {

      /// 符号已经存在
      free(symbol);
    }
  }

  /// 返回结果
  return token;
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
