#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>

int main()
{
int row,n,i,m,a,b,c,d;
printf("row?\n");
scanf("%d",&row);

//upper
for(n=0;n<=row-1;++n)
{

for(m=1;m<=row-n;++m)
{
    printf(" ");

}


for(i=1;i<=(2*n+1);++i)
{
    printf("*");
}

printf("\n");
}


//lower
for(a=0;a<=row-2;++a)
{

for(b=0;b<=a+1;++b)
{
    printf(" ");

}


for(c=1;c<=2*(row-2-a)+1;++c)
{
    printf("*");
}

printf("\n");
}



return 0;
}
