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
typedef LIST *LISTPTR;

int add_to_list(int,LISTPTR);
void print_structure(LISTPTR);
void free_memory(LISTPTR);


int main()
{
    int ch,i=0;
    LISTPTR first=NULL;
    char trash[256];

    while(i++<5)
    {
        ch=0;
        printf("enter ur char \n");
        do
        {
            puts("must from A TO Z");
            ch=getc(stdin);
            gets(trash);

        }while((ch<'a'||ch>'z')&&(ch<'A'||ch>'Z'));

        first=add_to_list(ch,first);
    }

    print_structure(first);

    free_memory(first);

    if(first==NULL)
    {puts("first clean back to null");}
    else
    {
        puts("first not clean"); //free了还有占位
    }



    return 0;
}


int add_to_list(int ch, LISTPTR first)
{
    LISTPTR new_rec=NULL;
    LISTPTR tmp_rec=NULL;
    LISTPTR prev_rec=NULL;

    new_rec=(LISTPTR)malloc(sizeof(LIST));
    if(!new_rec)
    {
        puts("unable to allocate memory");
        exit(0);
    }

    new_rec->ch=ch;
    new_rec->next_rec=NULL;

    if(first==NULL)
    {

        new_rec->next_rec=first;
        first=new_rec;

    }

    else
    {
        if(first->ch > new_rec->ch)
        {
            new_rec->next_rec=first;
            first=new_rec;
        }
        else if((first->ch < new_rec->ch)&&(first->next_rec==NULL))
        {
            first->next_rec=new_rec;
            new_rec->next_rec=NULL;
        }

        else
        {
         prev_rec=first;
         tmp_rec=first->next_rec;
         while(tmp_rec->next_rec!=NULL)
         {
             if(new_rec->ch < tmp_rec->ch)
             {
                 new_rec->next_rec=tmp_rec;
                 if( new_rec->next_rec!=prev_rec->next_rec)
                 {
                     puts("error");
                     getc(stdin);//!!!
                     exit(1);

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



                if(new_rec->ch < tmp_rec->ch)
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



return(first);

}

void print_structure(LISTPTR first)
{
    LISTPTR cur_ptr;
    int i=1;

    printf("\n\nrec addr position data next rec addr\n");
    printf("======== ======== ==== =============\n");

    cur_ptr=first;

    while(cur_ptr!=NULL)
    {
        printf(" %x     ",cur_ptr);
        printf("  %2i     %c  ",i++,cur_ptr->ch);
        printf("    %x       \n",cur_ptr->next_rec);
        cur_ptr=cur_ptr->next_rec;


    }



}



void free_memory(LISTPTR first)
{
    LISTPTR cur_ptr,tmp;

    cur_ptr=first;
    while(cur_ptr!=NULL)
    {
        tmp=cur_ptr->next_rec;
        free(cur_ptr);
        cur_ptr=tmp;
    }

 if(cur_ptr==NULL)
    {puts("cur_ptr free back to null");}
    else
    {
        puts("cur_ptr not clean");
        printf("first  %c\n",first);//有占位
    }



}
