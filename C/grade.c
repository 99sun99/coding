#include<stdio.h>

int main()
{
 int mark;
 printf("enter ur mark\n");
 scanf("%d",&mark);
if (mark>100)
   printf("invalid");
else if (mark>80)// donnt need left part
   printf("A");
else if (mark>70)
   printf("B");
else if (mark>=60)
   printf("c");
else
   printf("failed");

return 0;

}
