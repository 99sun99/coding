#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


struct data
{
  char name[80];

  struct data *next;


};


typedef struct data PERSON;//不用再写一大坨了，带着struct
typedef PERSON *LINK; //规定个指针指向这个结构 有*



int main()

{
    LINK head=NULL;
    LINK current=NULL;
    LINK new=NULL;

    new = (LINK)malloc(sizeof(PERSON));//分配了一块内存给link指向的数据结构
    new -> next = head;//把头赋给指针，第一个指针给头,这句必须在前面！！！
    head=new;//感觉是自己指着自己
    new->next=NULL;//冗余但是保证安全
    strcpy(new->name,"A");

    current=head;//找最后的启动项
    while(current->next!=NULL) //不是最后的情况下，不停的赋值直到最后一个再从end加入
    {

        current=current->next;//动起来

    }
    new=(LINK)malloc(sizeof(PERSON));
    current->next=new;//head 到next又有了一个地址
    new->next=NULL;
    strcpy(new->name,"C");//对于这个时刻来说的指向name的指针是C的地址

    /* 也可以
       new=(LINK)malloc(sizeof(PERSON));
    new->next=current->next;
    current->next=new;
    strcpy(new->name,"C");
    */


    new=(LINK)malloc(sizeof(PERSON));
    new->next=head->next;//变哪块就改哪块指针。指针赋值
    head->next=new;//
    strcpy(new->name,"B");

    current=head;
    //while(current->next!=NULL) //这句没有最后一个尾部的名字，因为，最后一块指向的是NULL但是块本身还有东西
    while(current!=NULL)
    {
        printf("\n %s",current->name);//print(name)
        current=current->next;//下移，把current本身的链接变成urrent指向的下一个链接
    }

    printf("\n");




    return  0;
}


/*
do while


Unlike the
while statement, a do...while loop executes its statements at least once.
Example 1
/ prints even though condition fails!
int x = 10;
do
{
printf(“\nThe value of x is %d”, x );
}while (x != 10);
Example 2
/* gets numbers until the number is greater than 99
int nbr;
do
{
scanf(“%d”, &nbr );
}while (nbr <= 99);
Example 3
//* Enables user to enter up to 10 integer values
//* Values are stored in an array named value. If 99 is
//* entered, the loop stops
int value[10];
int ctr = 0;
int nbr;
do
{
puts(“Enter a number, 99 to quit “);
scanf( “%d”, &nbr);
value[ctr] = nbr;
ctr++;
}while (ctr < 10 && nbr != 99);

*/


//list
/*

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define max 25


#ifndef NULL
    #define NULL 0
#endif

struct list
{
  int ch;

  struct list *next_rec;

};

typedef struct list LIST;
typedef LIST *LISTPTR;

LISTPTR add_to_list(int, LISTPTR);
void show_list(LISTPTR);
void free_memory_list(LISTPTR);

int main()
{
    LISTPTR first=NULL;//head
    int i=0;
    int ch;
    char trash[256];

    while(i++<5)
    {
        ch=0;
        printf("\n enter character %d",i);

        do
        {
            printf("\nmust be a to z:");
            ch=getc(stdin);//P346 book not pdf
            gets(trash);//如果输入的是很多字母那么第一个取走了，剩下的trash放在这里
        }while((ch<'a'||ch>'z')&&(ch<'A'||ch>'Z')); //传的数才好比较 用int 好比较？

        first=add_to_list(ch,first);


    }

    show_list(first);
    free_memory_list(first);

    return 0;


}

LISTPTR add_to_list(int ch,LISTPTR first)
{
    LISTPTR new_rec=NULL;
    LISTPTR tmp_rec=NULL;
    LISTPTR prev_rec=NULL;

    new_rec=(LISTPTR)malloc(sizeof(LIST));
    if(!new_rec)//如果内存数据为0，用！表示
    {
        printf("\nunable to allocate memory!\n");
        exit(-1);
    }

    new_rec->ch=ch;//把ata灌进去
    new_rec->next_rec =NULL;

    if(first==NULL)
    {
        first=new_rec;
        new_rec->next_rec=NULL;
    }
    else
    {
      if(new_rec->ch<first->ch)
      {
          new_rec->next_rec=first;//把小的变成头，不是把头换回去
          first=new_rec; //再把irst的连接换了（当是左边吧）
      }
      else
      {

          tmp_rec=first->next_rec;
          prev_rec=first;

          if (tmp_rec==NULL)
          {
              prev_rec->next_rec=new_rec;


          }
          else
          {
              while((tmp_rec->next_rec!=NULL))
              {
                  if(new_rec->ch<tmp_rec->ch)//new在tmp前面
                  {
                      new_rec->next_rec=tmp_rec;
                      if(new_rec->next_rec!=prev_rec->next_rec)
                      {
                          printf("error!\n");
                          getc(stdin);
                          exit(0);
                      }
                      prev_rec->next_rec=new_rec;
                      break;
                  }
                  else//正常情况
                  {
                      tmp_rec=tmp_rec->next_rec;
                      prev_rec=prev_rec->next_rec;


                  }
              }

              if(tmp_rec->next_rec==NULL)
              {

                  if(new_rec->ch< tmp_rec ->ch)
                  {
                      new_rec->next_rec=tmp_rec;//new变成倒数第二块
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







   return (first);
}


void show_list(LISTPTR first)
{
    LISTPTR cur_ptr;
    int counter=1;

    printf("\n\nREC addr Position Data Next Rec addr\n");
    printf("======== ======== ==== =============\n");
    cur_ptr=first;
    while(cur_ptr!=NULL)
    {
        printf(" %X     ",cur_ptr);
        printf(" %2i     %c",counter++,cur_ptr->ch);
        printf("    %X  \n",cur_ptr->next_rec);
        cur_ptr=cur_ptr->next_rec;




    }






}

void free_memory_list(LISTPTR first)
{
    LISTPTR cur_ptr,next_rec;
    cur_ptr=first;

    while(cur_ptr!=NULL)
    {
        next_rec=cur_ptr->next_rec;
        free(cur_ptr);
        cur_ptr=next_rec;


    }


}




*/

/*

 int main()
 {

    int ch;
    while ((ch = getchar()) != '\n')

      putchar(ch);//输出,each key 全部输出



    return 0;


 }
*/

/*




int main()
{
    int count;
    char message[] = "Displayed with putchar().";
    for (count = 14; count < 128; )

    {printf("%d=",count);
        putchar(count++);
    printf("\n");  //不同的数字有不同的char对应值

    }
for (count = 0; count < MAXSTRING; count++)
{

        putchar(message[count]);
}

    return 0;
}

*/

/*

int main()
{
    char str1[50];
    printf("Input a string:\n");
    gets(str1);
    printf("%s\n",str1);

 char chc;
   printf("Input a character:\n");

    chc=getc(stdin);
    gets(str1); //比如上面输入kjdf,实际只取k,后面的jdf落在其他数组里面，以免多余干扰，这个就是rash
    printf("%s\n",str1);
    printf("%c\n",chc);
    //puts(chc);//这个就不行

        int chc;//一般用int getc就是取得char的意思
    printf("Input a character:\n");

    chc=getc(stdin);
    //gets(str1);
    //printf("%s\n",str1);
    printf("%\c\n",chc);


     char ch;
    printf("Input a string:\n");
    ch=getch(); //可以用来作为“press any key to continue”的实现
    //getch 类似 getchar  	getch从控制台无回显地取一个字符 ,在调试时,在关键位置显示有关的结果以待查看,然后用getch函数暂停程序运行,当按任意键后程序继续运行.
    printf("%c\n",ch);




    return 0;
}


int main()

{
    int ch;
    int trash[200];

    ch=getc(stdin);

    gets(trash);

    putchar(ch);//不换行了
    getchar();//换行用
    //puts(ch);//不行
    puts(trash);




    return 0;





}

*/


/*

#include<stdlib.h>
#include<stdio.h>
#include<string.h>

struct list
{
   int ch;

   struct list *next_rec;

};

typedef struct list LIST;
typedef LIST *LISTPTR;

LISTPTR add_to_list(int ch,LISTPTR);
void show_list(LISTPTR);
void free_memory_list(LISTPTR);


int main()
{
    LISTPTR first=NULL;

    int i=0;、
    int ch;//char ch好像也行，但是不知道是什么情况，C语言可以自动转换？
    char trash[256];
    while(i++<5)
    {
     ch=0;//为了好比较
     printf("enter ur %d character\n",i);
     do
     {
         printf("must be a to z, lower or higher\n");
         ch=getc(stdin);
            gets(trash);
     }while((ch<'a'||ch>'z')&&(ch<'A'||ch>'Z'));//用int 好比较？

     first=add_to_list(ch,first);





    }

    show_list(first);
    free_memory_list(first);


    return 0;
}

LISTPTR add_to_list(int ch, LISTPTR first)
{
        LISTPTR new_rec=NULL;
        LISTPTR tmp_rec=NULL;
        LISTPTR prev_rec=NULL;

        new_rec=(LISTPTR)malloc(sizeof(LIST));
        if(!new_rec)
        {
            printf("\n unable to enter !\n");
            exit(1);
        }

        //赋到结构里面了
        new_rec->ch=ch;
        new_rec->next_rec=NULL;

        if(first==NULL)
        {
           first=new_rec;
           new_rec->next_rec=NULL;

        }

        else
        {
        if(new_rec->ch<first->ch)//因为如果不是head这时候上一块的，这时候有赋值
        {
            new_rec->next_rec=first;//自己指着自己，头,first不用动因为是别人指着自己
            first=new_rec;//把new_rec的空间给first
        }
        else
        {
            tmp_rec=first->next_rec;
            prev_rec=first;


          if(tmp_rec == NULL)//最后一个
        {
            prev_rec->next_rec=new_rec;//正常大小直接add end
        }
        else
        {
            while((tmp_rec->next_rec!=NULL))//中间
            {
                if(new_rec->ch<tmp_rec->ch)//新的比原来小，放前面
                {

                    new_rec->next_rec=tmp_rec;
                    if(new_rec->next_rec!=prev_rec->next_rec)//赋值之后出错了，不写也行
                    {
                        printf("error\n");
                        getc(stdin);
                        exit(0);
                    }
                    prev_rec->next_rec=new_rec;//都没问题可以赋值了
                    break;//break from while

                }
                    else//不是最后一个
                    {
                        tmp_rec=tmp_rec->next_rec;
                        prev_rec=prev_rec->next_rec;
                    }





            }


            if(tmp_rec->next_rec==NULL)
        {
            if(new_rec->ch<tmp_rec->ch)
            {
                new_rec->next_rec=tmp_rec;
                prev_rec->next_rec=new_rec;//prev是first即传进来之前的数
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




 return (first);


}


void show_list(LISTPTR first)
{

    LISTPTR cur_ptr;
    int counter=1;

    printf("\n\nRec addr position data next rec addr\n");
    printf("======== ======== ==== =============\n");

    cur_ptr=first;
    while(cur_ptr!=NULL)
    {

    printf("%d      ",cur_ptr);
    printf("  %2i    %c",counter++,cur_ptr->ch);
    printf("    %d       \n",cur_ptr->next_rec);
    cur_ptr=cur_ptr->next_rec;


    }







}

void free_memory_list(LISTPTR first)
{
    LISTPTR cur_ptr,next_rec;
    cur_ptr=first;

    while(cur_ptr!=NULL)
    {
        next_rec=cur_ptr->next_rec;
        free(cur_ptr);
        cur_ptr=next_rec;


    }




}
*/

/*
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#ifndef NULL
    #define NULL 0
#endif

struct list
{
    int ch;
    struct list *next_rec;

};

typedef struct list LIST;

typedef LIST  *LISTPTR;

LISTPTR add_to_list(int ch,LISTPTR first);
void show_list(LISTPTR);
void free_memory(LISTPTR);

int main()
{
    LISTPTR first=NULL;
    int i=0,ch;
    char trash[200];

    while(i++<5)
    {
        ch=0;
        printf("enter ur character\n");

        do
        {
            printf("must be A to Z\n");
            ch=getc(stdin);
            gets(trash);
        }while((ch<'a'||ch>'z')&&(ch<'A'||ch>'Z'));


     first=add_to_list(ch,first);

    }

  show_list(first);
 free_memory(first);





    return 0;
}


LISTPTR add_to_list(int ch,LISTPTR first)
{
    LISTPTR new_rec=NULL;
    LISTPTR tmp_rec=NULL;
    LISTPTR prev_rec=NULL;

    new_rec=(LISTPTR)malloc(sizeof(LIST));
    if(!new_rec)
    {
        puts("error");
        exit(1);
    }

    new_rec->ch=ch;
    new_rec->next_rec=NULL;//先变成单独一块儿

    if(first == NULL)
    {
        new_rec->next_rec=first;
        first=new_rec;
        //first=new_rec;
        //new_rec->next_rec=NULL;

    }

    else
    {
        if(new_rec->ch<first->ch)
        {
            new_rec->next_rec=first;
            first=new_rec;//改变头指针
        }

        else
        {
           tmp_rec=first->next_rec;
           prev_rec=first;


           if(tmp_rec==NULL)
           {

               prev_rec->next_rec=new_rec;


           }
           else
           {
               while((tmp_rec->next_rec!=NULL))
               {

                   if(new_rec->ch<tmp_rec->ch)

                   {
                      new_rec->next_rec= tmp_rec;
                     if(new_rec->next_rec!=prev_rec->next_rec)
                     {
                         printf("error");//随手查错误
                         getc(stdin);
                         exit(0);

                     }
                     prev_rec->next_rec=new_rec;
                     break;

                   }

                else
                {
                    tmp_rec=tmp_rec->next_rec;
                    prev_rec=prev_rec->next_rec;
                }



               }

            if(tmp_rec->next_rec==NULL)
            {
                if(new_rec->ch <tmp_rec->ch)
                {
                    new_rec->next_rec=tmp_rec;
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





    return (first);
}

void show_list(LISTPTR first)

{
    LISTPTR cur_ptr;
    int counter=1;



    printf("\n\nrec addr position data next rec addr\n");
    printf("======== ======== ==== ============\n");

    cur_ptr=first;
    while(cur_ptr!=NULL)
    {
        printf(" %x      ",cur_ptr);
        printf(" %2i       %c    ",counter++,cur_ptr->ch);
        printf("   %x \n",cur_ptr->next_rec);

        cur_ptr=cur_ptr->next_rec;



    }



}



void free_memory(LISTPTR first)
{

    LISTPTR  cur_ptr,tmp_rec;
    cur_ptr=first;



    while(cur_ptr!=NULL)
    {
        tmp_rec=cur_ptr->next_rec;//先存起来
        free(cur_ptr);

        cur_ptr=tmp_rec;


    }

}

*/


/*
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

struct kilo
{
    struct kilo *next;
    char dummy[1020];

};
int FreeMem(void);



int main()
{
    printf("You have %d kilobytes free.\n", FreeMem());


    return 0;
}

int FreeMem(void)
{

    long counter;
    struct kilo *head, *current, *nextone;

    current = head = (struct kilo*) malloc(sizeof(struct kilo));

    if (head == NULL)
    return 0;

    counter = 0;
    do
{
counter++;

current->next = (struct kilo*) malloc(sizeof(struct kilo));
current = current->next;
//printf("\r%d",counter);
} while (current!=NULL);

current = head;

do
{
nextone = current->next;
free(current);
current = nextone;
 } while (nextone != NULL);

return counter;
}


*/


