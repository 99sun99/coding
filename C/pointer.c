#include <stdio.h>
#include <string.h>
int main()
{
 int rate, *p_rate, *list;

 rate=100;

 int array[6];

 array[0]=1;
 array[1]=2;
 array[2]=3;

 list=array;
 p_rate=&rate;//Initializing Pointers
 //rate=*p_rate;//不可以只能从地址赋值

printf("rate=%d    rateaddress=%d    \np_pointer=%d    pointer=%d \n array=%d address=%d",rate,&rate,*p_rate,p_rate,&array,list);//*array,*list  这俩结果一样 &array list array这三个一样

return 0;
}

/*
int main()
{
 int a ,b[1000];

 for(a=0;a<6;++a)
 {
     printf("a=%d  pointer=%d\n",a,&a);
 }

 //pointer not change

printf("\n");

  for(a=0;a<6;++a)
 {
     b[a]=a;
     printf("b[a] =%d  pointer=%d\n",b[a],&b[a]);
 }  //P202 21 days teach ur self , 4 bytes


 return 0;
}

*/

/*
int main()
{
int a[max]={1,2,3},b=0, *c;
printf("%d  %d\n",b, &b);

 scanf("%d",&b);//b的地址存储了新的数，为输入进去的数

 printf("%d  %d",b, &b);
 return 0;
}


*/


/*

int main()
{


int i,a,*b,array[1000],*c;

 printf("enter address\n");
 scanf("%d",&a);
 printf("array?\n");
 for(i=0;i<=10;++i)
 {
     array[i]= i+1;
 }

 b=&a;
 c=array;

 printf("a=%d a address=%d\n b*=a=%d b address=%d\n  c=%d  *c=%d\n &array[0]=%d addr array=%d\n  array4=%d addr=%d",a,&a,*b,b,c,*c,&array[0],array,array[4],&array[4]);
//没有 *array[] 本身就不是指针  有 *(array+4)
printf("\n &b=%d",&b);
//*b=从谁传过来的  b=引过来之前的位置 &b引过来之后的位置
//array &array[0] 都是list头指针的意思
 return 0;
}


*/


/*
int main()
{
 int i,a,*b,array[1000],*c;
for(i=0;i<=10;++i)
 {
     array[i]= i+1;
 }


printf("*array=%d  *(array+4)=%d ",*array,*(array+4));

 return 0;
}


*/



/*
int main( )
{
int count;

char *message[8] = { "Four", "score", "and", "seven","years", "ago", "our", "forefathers" } ;
//这样不行 char b[] = { "Four", "score", "and", "seven","years", "ago", "our", "forefathers" } ;
//21天 P426 FIGURE 15.4 原理 自动分配成a=&b的形式 只不过是倒回去的 图上写的很清楚 这种时候 一个字母占一位
//只能这样 char string[10] = { 'A', 'l', 'a', 'b', 'a', 'm', 'a','\0'};
char b[10] = { 'A', 'l', 'a', 'b', 'a', 'm', 'a','\0'};
int c[5]={1,2,3};

for (count = 0; count < 8; count++)
{printf("%d ", *message[count]);}
printf("\n");
for (count = 0; count < 8; count++)
{printf("%s ", message[count]);}
printf("\n");
for (count = 0; count < 8; count++)
{printf("%d ", &message[count]);}
printf("\n");

for (count = 0; c[count]!='\0'; count++)
{printf("%d ", c[count]);}
printf("\n");


for (count = 0; b[count]!='\0'; count++)
{printf("%d ", b[count]);}

printf("\n");
//因为作为数字可以直接输出 但是作为


printf("%d\n",message[3]);

printf("b[3]=%c",b[3]);
//没法输出词组，只能化成指针  实际上是数字的形式
//21天 P426 FIGURE 15.4 原理 自动分配成a=&b的形式 只不过是倒回去的
//就不用 char message[8] = "four score and seven years ago our forefathers "
//但是出来的是 four sco  这个时候一个字母变成一个元素，上面是告诉了多少个字母是一个元素

return 0;

}


*/
