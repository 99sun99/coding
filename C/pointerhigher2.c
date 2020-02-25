/*



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
int myVar = 12;
int *ptr = &myVar;
int **ptr_to_ptr = &ptr;//或者以开头的形式声明
//int **ptr_to_ptr;
//**ptr_to_ptr = &ptr;不行
//*ptr_to_ptr = &ptr;不行
//ptr_to_ptr = &ptr;可以
printf("%d  %d   %d  %d  %d  %d  %d %d %d" ,*ptr,   ptr,       &ptr,  myVar,&myVar,**ptr_to_ptr,*ptr_to_ptr,ptr_to_ptr,&ptr_to_ptr);
//result                                     12  6356732      6356728  12   6356732  12           6356732     6356728    6356724
//&ptr=ptr_to_ptr
//*ptr=myVar=**ptr_to_ptr
//ptr=&myVar=*ptr_to_ptr
//&ptr_to_ptr
    return 0;

}



*/


/*
void func1(void (*p) (void));
void one(void);
void two(void);
void other(void);

int main()
{
    int val;
    void (*ptr)(void);


  for(;;)
{
    puts("enter");
    scanf("%d",&val);
    if(val==0)
    {
        puts("error");
        break;
    }
    else if(val==1)
    {
        ptr=one;
    }
    else if(val==2)
    {
        ptr=two;
    }
    else
    {
        ptr=other;
    }

    func1(ptr);//必须有 要么就直接用ptr()；

}

    return 0;

}


void func1(void (*p)(void))
{
   p();//代表要执行的意思

}

void one(void)
{
    puts("u enter one");

}
void two(void)
{
    puts("u enter two");
}
void other(void)
{
    puts("other number");
}


*/

/*
void func1(int);
void one(void);
void two(void);
void other(void);

int main()
{
    int val;



  for(;;)
{
    puts("enter");
    scanf("%d",&val);
    if(val==0)
    {
        puts("break");
        break;
    }

    func1(val);

}

    return 0;

}


void func1(int n)
{
     void (*p)(void);
    if(n==1)
    {
        p=one;
    }
    else if(n==2)
    {
        p=two;
    }
    else
    {
        p=other;
    }

  p();//这句必须有了

}

void one(void)
{
    puts("u enter one");

}
void two(void)
{
    puts("u enter two");
}
void other(void)
{
    puts("other number");
}


*/

/*
//while true 使用
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> //true 用

void func1(void (*p) (void));
void one(void);
void two(void);
void other(void);

int main()
{
    int val;
    void (*ptr)(void);


  while( true )
{
    puts("enter");
    scanf("%d",&val);
    if(val==0)
    {
        puts("error");
        break;
    }
    else if(val==1)
    {
        ptr=one;
    }
    else if(val==2)
    {
        ptr=two;
    }
    else
    {
        ptr=other;
    }

    ptr();

}

    return 0;

}


void func1(void (*p)(void))
{
   p();//代表要执行的意思

}

void one(void)
{
    puts("u enter one");

}
void two(void)
{
    puts("u enter two");
}
void other(void)
{
    puts("other number");
}


*/

/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max 25  //好习惯随手写
int get_line(char *lines[]);
void sort(char *lines[],int n);
void print_lines(char *lines[],int n);
char *lines[max];

int main()

{
    int m;


    m=get_line(lines);
    if(m<0)
    {
        printf("error!");
        exit(-1);
    }


    sort(lines,m);
    print_lines(lines,m);


    return 0;
}


int get_line(char *lines[])
{
    int i=0;
    char buffer[80];
    puts("enter one word a line ,tab space to finish ");

    while((i<max)&&(gets(buffer)!=0)&&(buffer[0]!='\0'))
    {
        if((lines[i]=(char *)malloc(strlen(buffer)+1))==NULL)
        {
            return -1;


        }
        strcpy(lines[i++],buffer);


    }
    return i;

}


void sort(char *lines[],int n)
{
    int a,b;
    char *swap;
    for(a=0;a<n;a++)
    {
        for(b=0;b<n-a-1;b++)
        {
            if(strcmp(lines[b],lines[b+1])>0)
            {swap=lines[b];
            lines[b]=lines[b+1];
            lines[b+1]=swap;
            }

            //{}问题

        }
    }




} //最后提示少了expression或者statement可能是前面有问题


void print_lines(char *lines[],int n)

{
    int a;

    for(a=0;a<n;a++)
    {
        printf("%s \n", lines[a]);
    }


}
*/

/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define max 25  //好习惯随手写
int get_line(char *lines[]);
void sort(char *lines[],int n,int sort_type);
void print_lines(char *lines[],int n);
int  alpha(char *p1,char *p2);
int  rev(char *p1,char *p2);
int bubble(char *p1,char *p2);

char *lines[max];



int main()

{
    int m,sort_type;


    m=get_line(lines);
    if(m<0)
    {
        printf("error!");
        exit(-1);
    }

    puts("1 for alpha sort, 0 for reversion");
    scanf("%d",&sort_type);
    sort(lines,m,sort_type);
    print_lines(lines,m);


    return 0;
}


int get_line(char *lines[])
{
    int i=0;
    char buffer[80];
    puts("enter one word a line ,tab space to finish ");

    while((i<max)&&(gets(buffer)!=0)&&(buffer[0]!='\0'))
    {
        if((lines[i]=(char *)malloc(strlen(buffer)+1))==NULL) //单纯用strcpy得allocatespace，这里用了gets
        {
            return -1;
        }
        strcpy(lines[i++],buffer);
        //lines[i++]=buffer;//不行因为感觉是赋的是数字不是char,涉及指针，直接赋值会不准确，用trcpy会找到地址,
        //指针没有初始化不能直接被赋值，要初始化一个位置比如  *p, p=&a  ，或者 ptr=square 函数，给了位置才能赋值要不会找不到赋值不准
        //要用trcpy因为连着指针一起copy了而不是只copy数值

    }
    return i;

}


void sort(char *lines[],int n,int sort_type)
{
    int a,b;
    char *swap;
    int (*compare) (char *c,char *d);//指针指向函数，这个函数是啥呢，根据sort type决定

    compare = (sort_type) ?  alpha:rev; //只能1,0两个,左边1 右边0
    compare (lines[0],lines[1]);

    for(a=1;a<n;a++)
    {
        for(b=0;b<n-1;b++)
        {
            if( compare (lines[b],lines[b+1]) >0)
            {swap=lines[b];
            lines[b]=lines[b+1];
            lines[b+1]=swap;
            }



        }
    }




}

int  alpha(char *p1,char *p2)
{       puts("alpha");

    return (strcmp(p1,p2));
}
int  rev(char *p1,char *p2)
{       puts("rev");


    return (strcmp(p2,p1));
}





void print_lines(char *lines[],int n)

{
    int a;

    for(a=0;a<n;a++)
    {
        printf("%s \n", lines[a]);
    }


}

*/
