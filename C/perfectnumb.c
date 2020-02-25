#include<stdio.h>
#include<stdlib.h>
#include<math.h>


int main()
{
 int n,i,x=0,y;

printf("enter ur num\n");
scanf("%d",&n);

for(i=1;i<n;++i)

 {
 if(n%i==0)
  x=x+i ;
 }



 if(x== n)
 printf("perfect num! \n");

 else

 printf("not perfect\n");



 return 0;
}
