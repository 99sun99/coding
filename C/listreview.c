#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#ifndef NULL
    #define NULL 0
#endif

struct list
{
  int ch;


  struct list  *next_rec;

};
//}test;//不行不是指针

typedef struct list  LIST;
typedef LIST *LISTPTR;

LISTPTR add_mumber(int, LISTPTR);
void show_list(LISTPTR);
void free_memory(LISTPTR);

int main()
{

    LISTPTR first=NULL;

        int ch,i=0;
        char trash[256];

        while(i++<5)
        {
            ch=0;//为了落在外面
            printf("enter a char\n");

            do
            {
                printf("it must be a to z,lower or upper\n");
                ch=getc(stdin);
                gets(trash);
            }while((ch<'a'||ch>'z')&&(ch<'A'||ch>'Z'));//落在外面了所以要进来

            first=add_mumber(ch,first);

        }

show_list(first);

//printf("%c",LIST.ch);  //这里不能这么写，可以写 new->ch啥的
//printf("after show list %c",test.ch);
printf("after show list %c",(*first).ch);//指针的用法，等于first->ch的用法



free_memory(first);


return 0;

}


LISTPTR add_mumber(int ch, LISTPTR first )
{

  LISTPTR new_rec=NULL;
  LISTPTR prev_rec=NULL;
  LISTPTR tmp_rec=NULL;

  new_rec=(LISTPTR)malloc(sizeof(LIST));
  if(!new_rec)
  {
      puts("unable to allocate\n");
      exit(1);
  }

  new_rec->ch=ch;
  new_rec->next_rec=NULL;

  if(first==NULL)//地址有null 0呗。
  {
      new_rec->next_rec=first;
      first=new_rec;
  }
  else
  {
        if(new_rec->ch < first->ch)
            {

               new_rec->next_rec=first;
               first= new_rec;//first给出去了之后，才能把first的地址改变了
               //new_rec->next_rec=first; //不可以，first已经变啦

            }

        /*else if((new_rec->ch>first->ch)&&(first->next_rec=NULL))
        {
            first->next_rec=new_rec;
        }*/

        else
        {

           tmp_rec=first->next_rec;
           prev_rec=first;


           if(tmp_rec == NULL)//没有这个东西
           {
               prev_rec->next_rec=new_rec;
           }


        else{
           while((tmp_rec->next_rec!=NULL))//唯一条件要放前面
           {

               if(new_rec->ch < tmp_rec->ch)//没必要用高很多while
               {
                   new_rec->next_rec=tmp_rec;//校验，可以同时指向一个，但反过来没法检验了,移动指针才检验
                   if(new_rec->next_rec!=prev_rec->next_rec)
                   {
                       printf("error\n");
                       getc(stdin);//小错
                       exit(0);
                   }

                   prev_rec->next_rec=new_rec;
                    break;//不加看不出来gdhe的e，会报错，指针乱了，用break直接跳到return

               }

             else //(new_rec->ch>=tmp_rec->ch) else放后面，因为不知道都有什么情况
               {
                    /*这句不行 没按照顺序来，因为它连了同一块了，不能把顺序弄瞎了
                   prev_rec=prev_rec->next_rec;
                   tmp_rec=tmp_rec->next_rec;
                   */
                   tmp_rec=tmp_rec->next_rec;
                   prev_rec=prev_rec->next_rec;


               }

           }

            if(tmp_rec->next_rec==NULL)//等号问题
           {
               if(new_rec->ch<tmp_rec->ch)
               {

                   new_rec->next_rec=tmp_rec;
                   //前面测过了
                   prev_rec->next_rec=new_rec;

               }
               else
               {
                   tmp_rec->next_rec=new_rec;
                   new_rec->next_rec=NULL;
               }

           }



        }


        }

  }



  return(first);

}

void show_list(LISTPTR first)
{
    LISTPTR cur_ptr;
    int i=8;

    printf("\n\nrec addr position data next rec addr\n");
    printf("======== ======== ==== =============\n");
    cur_ptr=first;

    while(cur_ptr!=NULL)
    {
        printf("%x      ",cur_ptr);
        printf(" %2i    %c   ",i++,cur_ptr->ch);//2i右对齐
        printf("    %x      \n",cur_ptr->next_rec);

        cur_ptr=cur_ptr->next_rec;

    }




}

void free_memory(LISTPTR first)

{
    LISTPTR tmp,cur_ptr;

    cur_ptr=first;
    printf("\n begin to clear %c\n",cur_ptr->ch);
    while(cur_ptr!=NULL)
    {
        tmp=cur_ptr->next_rec;
        free(cur_ptr);
        cur_ptr=tmp;


    }

    if(cur_ptr==NULL)
    {puts("null");}
    else
    {
        puts("else");
    }




}
