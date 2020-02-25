#include<stdio.h>

int main()
{
 int a,b,c;
 printf(" 3 number a b c u want to compare\n");
 scanf("%d %d %d",&a,&b,&c);//have to write in the same line

 if  (a>b&&a>c)//&& both
     printf("%d is the largest",a);
 else if(b>c)
     printf("%d is the largest",b);
 else if(c==a==b)//2 = to compare
     printf("equal");
 else
     printf("%d is the largest",c);

 return 0;

}
