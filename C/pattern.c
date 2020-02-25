#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
//我的代码大大简化了时间复杂度哈哈哈哈哈哈哈哈 ，上面是我的
int main()
{
int row,n,i,m,a;
printf("row?\n");
scanf("%d",&row);

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
return 0;
}


/*

int main()
{
    int i,a,b,c,d,n;
    printf("row?");
    scanf("%d",&n);
c=n;

for(i=1;i<=n;++i)
{
    for(a=1;a<c;++a)
    {printf(" ");}

    --c;
    //d=2*i-1;
    //for(b=1;b<=d;++b)
    for(b=1;b<=2*i-1;++b)
    {
        printf("*");
    }

    printf("\n");

}

   return 0;
}

*/
