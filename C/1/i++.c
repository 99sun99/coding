#include<stdio.h>

int main()

{
    int i=0;

    while(++i)

    {
        printf("i=%d\n",i);

        if(i==3)  break;

     }

    printf("i=%d\n",i);
}
