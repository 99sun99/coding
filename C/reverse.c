#include<stdio.h>

int main()
{
 int n,reverse=0; // need a intiative number

 printf("enter ur number to reverse\n");
 scanf("%d",&n);

 while (n !=0)
 {
   reverse=reverse*10; //give a unit
   reverse=reverse +n%10;

  n=n/10;

 }


 return reverse;



}
