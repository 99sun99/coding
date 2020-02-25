#include<stdio.h>

int main()
{
 int a,b,add,subtract,multiply;
 float divide;
 printf("enter ur number\n");
 scanf("%d %d",&a,&b);

 add = a+b;
 subtract = a-b;
 multiply = a*b;
 divide = a/(float)b;//put (float) in the dividend

 printf("sum = %d\n",add);
 printf("difference = %d\n",subtract);
 printf("multiplication = %d\n",multiply);
 printf("division = %.4f\n",divide);

 return 0;
}
