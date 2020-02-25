#include<stdio.h>



long gcd(long,long);//global

int main()
{

 long x,y,hcf,lcm;

 printf("please,enter 2 integers\n");
 scanf("%ld %ld",&x,&y);
 hcf=gcd(x,y);
 lcm=(x*y)/hcf;

printf("greatest is %ld\n",hcf);
printf("least is %ld\n",lcm);

return 0;
}

long gcd(long x,long y)//after int main cus  int x,y first
{
 if(x==0){return y;}

 while(y!=0)
 {
  if(x>y)
  x=x-y;//eg 25,2 25-12*2 is a circle until x=1
  else
  y=y-x;//until y=0 x is the GCD， y!=0 is the condition so else include y=x let y=0 so we jump out of the loop
 }

 return x;//remaind problem
}




