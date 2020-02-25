#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>

int main()
{
 int n,c,k;

 printf("enter ur number to change");
 scanf("%d",&n);

 for (c=31;c>=0;c--)
 {
     k=n>>c;
     if(k&1)
     printf("1");
     else
     printf("0");

 }

 return 0;
}


/*
八位可以直接转换哈！

int main()
{
 int n,c,k;

 printf("?\n");
 scanf("%d",&n);

 k=n;

 printf("octal=%lo",k);



 return 0;
}




*/

