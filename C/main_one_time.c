#include<stdio.h>
//一个main只能用一次
int main()
{
    int a ,first,second,sum;  //declare a variance
    printf("enter a integer ^_^\n");
    scanf("%d",&a); //scanf &!!
    printf("the integer u enter is %d\n",a);


    printf("enter two integers to add\n");
    scanf("%d%d",&first,&second);
    sum=first+second;
    printf("sum of entered numbers is %d\n ",sum);

    return 0;
}
