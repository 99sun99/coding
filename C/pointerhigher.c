#include <stdio.h>
#include <string.h>



int main()
{

printf("%d,%u\n",-123,-123);
 return 0;
}


/*
#include <stdio.h>
#include <string.h>
int main() // %u %d 不想把符号（负号）读出来的时候
{

int multi[2][4];


printf("\nThe size of multi = %u",(-sizeof(multi)));
printf("\nThe size of multi[0] = %u",sizeof(multi[0]));
printf("\nThe size of multi[0][0] = %u\n",sizeof(multi[0][0]));
printf("=============================================================");
printf("\nThe size of multi = %d",(-sizeof(multi)));
printf("\nThe size of multi[0] = %d",sizeof(multi[0]));
printf("\nThe size of multi[0][0] = %d \n",sizeof(multi[0][0]));


 return 0;
}


*/


/*


void print1(int (*p)[4]);
void print2(int (*p)[4],int n);

int main( )
{
int (*p)[4],count; //指向四维数组的指针
int  multi[3][4]={{1,2,3,4},{5,6,7,8},{9,10,11,12}};

p=multi;

for(count=0;count<3;count++)//[3][4] 不代表能到[3]
{

    print1(p++);   //不停的移动位置 p是位置 是个形式符合格式就可以传 *p++ p++都行

}
printf("\n%d",**p);//p *p 都是地址了 因为*p本身指的就是指针，不是一组四个指针的数组

printf("\n%d",multi+3);


printf("\n");
puts("enter!");
getchar();
print2(multi,3);
printf("\n");

return 0;

}

void print1(int(*p)[4]) //这里把指针传递给了一个指着有四个元素的数组 这时候才能打印出来数组 之前就是指针 所以打不出来
{
    int *ptr ,count;
    ptr=(int *)p;//这里是int 也有不是int的要声明

    for(count=0;count<4;count++)
    {
        printf("\n%d",*ptr++);// 之前p就是指针 所以打不出来
    }


}

void print2(int(*p)[4],int n)
{
    int *ptr ,count; //*ptr 把*p从数组中解放出来，变成自由移动的指针，不然仅仅是指向每个数组的第一位
    ptr=(int *)p;

      for(count=0;count<(4*n);count++)
    {
        printf("\n%d",*ptr++);//指针移动12次,关心移动多少次。
    }


}

*/

/*
//pointer sort  lines
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAXLINES 25

int get_lines(char *lines[]);
void sort(char *p[],int n);
void print_strings(char *p[],int n);

char *lines[MAXLINES];

int main()
{
 int number_of_lines;

 number_of_lines=get_lines(lines);

 if(number_of_lines<0)
 {
  puts("memory allocation error");
  exit(-1);
 }

 sort(lines, number_of_lines);
 print_strings(lines,number_of_lines);



 return 0;
}

int get_lines(char*lines[])
{

 int n=0;
 char buffer[80];
 puts("enter one line at a time;enter a blank when done.\n");

 while((n<MAXLINES)&&(gets(buffer)!=0)&&(buffer[0]!='\0'))
 {
  if ((lines[n]=(char *)malloc(strlen(buffer)+1))==NULL)
      {return -1;}
  strcpy(lines[n++],buffer);
 }
 return n;
}


void sort(char *p[],int n)
{
int a,b;
char *tmp;

for(a=1;a<n;a++)
{
 for(b=0;b<(n-1);b++)
 {
  if(strcmp(p[b],p[b+1])>0)
  {
   tmp = p[b];
   p[b]=p[b+1];//把它按照位置处理的不是字母 第一位如果一样就按照第二位排序so abcd转码都有固定编号的 把字母变成指针好办事的样子。
   p[b+1]=tmp;
   printf("p[b]=%s  p[b+1]=%s\n",p[b],p[b+1]);
  }
 }
}
}




void print_strings(char *p[],int n)
{
int count;

for(count=0;count<n;count++)
{

 printf("%s\n",p[count]);

}



}






*/


/*
总结
char a[]="it is a string!" ; //已经告诉他们了这个维度，就不写了
printf("%s",a);

char b[10] = { 'A', 'l', 'a', 'b', 'a', 'm', 'a','\0'};
printf("%s",b);

char *message[8]= { "Four", "score", "and", "seven","years", "ago", "our", "forefathers" } ;
for (count = 0; count < 8; count++)
{printf("%s ", message[count]);}

int c[]={1,2,3};
for (count = 0; count < 8; count++)
{printf("%d ", c[count]);}

int array[]={1,2,3,4,5};
printf("*array=%d  *(array+4)=%d ",*array,*(array+4));


int (*ptr)[4] ；int *ptr [4]

一个指针指向四个元素的数组和后面一个有四个元素的指针


*/

/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 25

int get_lines(char *lines[]);//指向
void sort(char *p[],int n);
void print_lines(char *p[],int n);

char *lines[MAX];

int main()
{
    int number_of_lines;

    number_of_lines=get_lines(lines);

    if(number_of_lines<0)
    {
        puts("error!");
        exit(-1);
    }

    sort(lines,number_of_lines); //必须传递第一个指针

    print_lines(lines,number_of_lines);

return 0;

}

//多个char必须用指针，不带*的时候是char类型的地址
int get_lines(char *lines[])
{
    int n=0;
    char buffer[100];

    printf("enter ur lines with enter, finish to tab space\n");

    while((n<MAX)&&(gets(buffer)!=0)&&buffer[0]!='\0')  //()可以没有
    {//gets 如果EOF就gets不进来了
     if((lines[n]=(char *)malloc(strlen(buffer)+1))==NULL)//保证malloc是刚刚分进来的，+1是最后一位空的 如果空的代表出错了没写进来
     {
         return -1;
     }
     strcpy(lines[n++],buffer);

    }

    return n;
}


void sort (char *p[],int n)
{
    int a, b;
    char *tmp;


    for(a=0;a<n;a++)
    {
        for(b=0;b<n-1-a;b++) //bubble sort
        {
            if(strcmp(p[b],p[b+1])>0)
            {tmp=p[b];
            p[b]=p[b+1];
            p[b+1]=tmp;

            }
        }

    }



}
void print_lines(char *p[],int n)
{
    int count;
    for(count=0;count<n;count++)
    {
        printf("%s\n",p[count]);
    }

}



*/

/*
//training
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define max 15
//lines sort print
int get_lines(char *p[]);
void sort(char *p[],int n);

char *lines[max];

int main()

{
    int i,m;

    m=get_lines(lines);//有get不全的情况，会考虑exit

    if(m<0)
    {
        puts("error");
        exit(-1);
    }

    sort(lines,m);

    for(i=0;i<m;i++)
    {
        printf("%s\n",lines[i]); //string， lines[i]

    }




    return 0;
}

int get_lines(char *p[])

{
    int m=0;
    char buffer[100];

    puts("enter ur words tab space to stop");

    while((m<max)&&(gets(buffer)!=0)&&(buffer[0]!='\0'))//括号乱了
    {
        if((p[m]=(char *)malloc(strlen(buffer)+1))==NULL)//括号乱了
        {
            return -1;
        }

        strcpy(p[m++],buffer); //p[m]本次再起一个，地址分配空间为0否，p[m++]下一个开始copy

    }


    return m;


}

void sort(char *p[],int n)
{
    int a,b;
    char *swap;

    for(a=0;a<n;a++)
    {
        for(b=0;b<n-a-1;b++)
        {
            if(strcmp(p[b],p[b+1])>0) //没加括号
            {
            swap=p[b];
            p[b]=p[b+1];
            p[b+1]=swap;
            }


        }
    }


}




*/
