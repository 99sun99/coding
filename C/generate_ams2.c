#include<stdio.h>
#include<stdlib.h>
#include<math.h>

long find_am(int); //global

int x,n; //global

int main()
{

int i;

printf("enter the number u want to find as a maximum range\n");
scanf("%d",&n);

printf("the amstrong numbers are:\n");

for(x=0;x<=n;++x)

{
if (find_am(x)==1) //如果会用到下面最好弄成公共变量，要不会有找不到的情况，你告诉PC一下
printf("amstrong number is %d\n",x);
}

return 0;
}







long find_am(int a) //predetermin number
{
 int y,sum=0,count,b,i=0;

b=a;
if (b==0)
{
 i=1;  //非eturn的时候也要有结果
}

 while(b!=0)
{
 ++i;
 b=b/10;
 }

 count=i;

 //printf("total bits are %d\n",count); //了解循环用全部遍历

 while (a!=0)
 {
 y=a%10;
 sum=sum+pow(y,count);
 a=a/10;

 }

 if(sum==x)
 {return 1;}

return 0;

}

