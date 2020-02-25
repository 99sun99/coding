#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int n,x;//global variance
long check_am(int);
long count_bits(int);

int main()
{

printf("bits of ur number\n");
scanf("%d",&n);
printf("enter ur number\n");
scanf("%d",&x);

if (check_am(x)==1)
printf("it is an amstrong number\n");

else
printf("is not an amstrong number\n");
return 0;

}


long count_bits(int b)
{
 int i=0;

 while(b!=0)
 {
 ++i;
 b=b/10;
 }

 return i;
}



long check_am(int a) //predetermin number
{
 int y,sum=0,count;

 count=count_bits(a);

 while (a!=0)
 {
 y=a%10;
 sum=sum+pow(y,count);
 a=a/10;
 }


 if(sum==x)
 return 1;


 else
 return 0;


}


/*  感觉是写的比较简洁的一版，ams函数只是负责check不要把不同的数字输入也混进去，所以放在main里面或者单独放，时间复杂度如果要降低就是位数计算问题可以优化
long check_am(long);

int main()
{

long m,i;

printf("enter ur number!\n");
scanf("%d",&m);
printf("the ams nunbers contained in %d are\n",m);
for(i=0;i<=m;++i)
{printf(check_am(i));}

printf("finish!\n");
return 0;

}


long check_am(long n)
{
    long i=0,a,b=0,sum=0,c;
a=n;
while (a!=0)
{
    ++i;
    a=a/10;

}


b=n;
while(b!=0)
{
  c=b%10;
  sum=sum+pow(c,i);
  b=b/10;
}

if(n==sum)
{
    printf("%d \n",n);
}

return 0;
}

*/

