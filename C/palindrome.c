#include<stdio.h>

int main()
{

 int n,temp,reverse=0;

 printf("enter ur number\n");
 scanf("%d",&n);

 temp=n; //make a comparision


while(temp!=0)

 {
  reverse=reverse*10;
  reverse=reverse+temp%10;

  temp=temp/10;

 }

 if(n==reverse)
 printf("%d is palindrome\n",n);
 else
 printf("%d is not palindrome\n",n);

 return 0;
}
