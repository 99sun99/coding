#include<stdio.h>
#include<stdlib.h>
#include<math.h>
//应该是传参的时候指针内存出问题了
int main()
{
 int m,n,q;

 printf("enter!\n");
 scanf("%d %d",&n,&m);
 // scanf("%d %d\n",&n,&m); 不能有/n
 printf("m= %d,n=%d\n ",m,n);

q=m;
m=n;
n=q;

printf("m= %d,n=%d\n ",m,n);
//printf("m= %d",n);

return 0;

}

/*
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int n,x;//global variance
long check_am(int);
long count_bits(int )

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

}



long check_am(int a) //predetermin number
{
 int i,y,sum=0;
 while (a!=0)
 {
 y=a%10;
 sum=sum+pow(y,n);
 a=a/10;
 }

 if(sum==x)
 return 1;


 else
 return 0;


}

*/
