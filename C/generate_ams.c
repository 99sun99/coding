#include<stdio.h>
#include<stdlib.h>
#include<math.h>

long find_am(int); //global
long count_bits(int);
int x,n; //global

int main()
{

int i;

printf("enter the number u want to find as a maximum range\n");
scanf("%d",&n);

printf("the amstrong numbers are:\n");

for(x=0;x<=n;++x)

{
if (find_am(x)==1)
printf("amstrong number is %d\n",x);
}

return 0;//no void return is accepted
}


long count_bits(int b)
{
 int i=0;

if (b==0) //其他情况可以用if,要写前面 ，循环单独从下面开始不算上面
{return 1;} //单独的结果单独加{} return的时候此循环结束

while(b!=0) //不满足的时候eturn0
//if(b!=0) //没法循环!!! 除非if 嵌套在 while里面
 {
 ++i;
 b=b/10;
 }

/*while(b==0)
{
 i=1;
}*/
//if (b==0) //写后面会把hile最后那个结果算进去
//return 1;
//不满足hile 的其他情况返回的是0
 return i;
 //'else情况默认为return 0
}



long find_am(int a) //predetermin number
{
 int y,sum=0,count;

 count=count_bits(a); //函数间也可以相互引用
// printf("total bits are %d\n",count); //了解循环用全部遍历

 while (a!=0)
 {
 y=a%10;
 sum=sum+pow(y,count);
 a=a/10;
 }

if(sum==x)
{return 1;} //return之后，函数出结果 就不执行下面的return0 了，说明函数的一种情况可以直接从return出结果


return 0;

}

