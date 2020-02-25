#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>

int main()
{

int n,d,m ,c,first[10][10];
scanf("%d %d",&m,&n);
printf("enter array\n");

for(d=0;d<n;++d)
{
    for (c=0;c<m;++c)
    scanf("%d",&first[c][d]);
}

//add 对应相加就好

for(d=0;d<n;++d)
{
    for (c=0;c<m;++c)
    printf("%d\t",first[c][d]);//table output

    printf("\n");
}


return 0;
}

