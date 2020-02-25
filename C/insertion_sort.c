#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void insertion_sort(long[],long);

int main()
{
 long array[1000],i,n;

 printf("enter ur array number?\n");
 scanf("%d",&n);

 printf("enter ur array?\n");
 for(i=0;i<n;++i)
 {scanf("%d",&array[i]);}

 printf("insertion sort!\n");

 insertion_sort(array,n);

 printf("done!\n");
 printf("array:{");

 for(i=0;i<n-1;++i)
 {printf("%d ,",array[i]);

   }
if(i==n-1)
printf("%d ",array[i]);
printf("}");

return 0;

}




void insertion_sort(long list[],long n)
{

 long i,d,c,swap;

 for(d=0;d<=(n-1);++d) //在前半段类似气泡，
 {
    c=d;

  while(c>0&&list[c]<list[c-1])
  {

   swap=list[c];
   list[c]=list[c-1];
   list[c-1]=swap;
   --c;

  }


 }
 }





