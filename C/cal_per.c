#include<stdio.h>

int main()
{
int a,b,c,d,e,sum;
float per;

printf("\n enter ur number :");
scanf("%d%d%d%d%d",&a,&b,&c,&d,&e);// input without enter will stay in the same row

sum=a+b+c+d+e;
per=((a+b+c+d+e)/(float)500);//enough parenthsis

 printf("the percentage is %.4f",per); //.f

 return 0;

}
