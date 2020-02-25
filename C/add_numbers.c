#include<stdio.h>
// declaration print loop final
int main()
{
 int n,sum=0,c;

 printf("enter ur number\n");
 scanf("%d",&n);

 printf("enter %d integer\n",n);

  for(c=1;c<=n;c++) //4 blocks  ;means condition c++means function  for(initial, condition,calculation)
  {
    printf("%d\n",c);//output loop
    sum = sum + c;
  }

printf("sum of entered integer is %d\n",sum);

return 0;
}
/* another solution
 for(c=1;c<=n;c++) //4 blocks
  {
    printf("%d\n",c);//output loop

  }

printf("sum of entered integer is %d\n",c);

output c directly*/
