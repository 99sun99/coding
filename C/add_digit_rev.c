#include<stdio.h>
#include<math.h> //^ sign no use, pow is the power
// not sensitive to blocks in c and c++. evernote ,21 teach ur self C P34 ,C++ P43
int main()
{
 int n, sum=0,m,remainder;

 printf("enter a number\n");
 scanf("%d",&n);

 while(n!=0)
 {
  remainder=n%10;
  sum=sum +remainder;
  printf("%d\n",remainder);
  n=n/10; //or loop never stop
 }

 printf("sum = %d",sum);

 return 0;
}
