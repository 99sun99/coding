#include<stdio.h>

int main()
{
 int gross_salary,base;
 float da ,ta,sum;
 printf("enter ur basic salary");
 scanf("%d",&base);

 da=base*(12/(float)100);
 ta=base*(10/(float)100);

 sum=base+da+ta;

 printf("ur gross salary is %.4f",sum) ;

 return 0;
}
