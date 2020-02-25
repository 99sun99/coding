#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>

int main()
{
int m,n,x,y,A[20][20],B[20][20];

printf("enter row and columns\n");
scanf("%d %d",&x ,&y);

for(m=0;m<x;++m)
{
    for(n=0;n<y;++n)
    scanf("%d",&A[m][n]);
}

for(m=0;m<y;++m)
{
    for(n=0;n<x;++n)
    B[m][n]=A[n][m];
}

printf("original\n");
for(m=0;m<x;++m)
{
    for(n=0;n<y;++n)
    printf("%d\t",A[m][n]);
    printf("\n");
}


printf("transpose\n");
for(m=0;m<y;++m)
{
    for(n=0;n<x;++n)
    printf("%d\t",B[m][n]);
    printf("\n");
}


return 0;
}

