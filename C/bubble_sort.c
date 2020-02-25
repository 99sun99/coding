#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void bubble_sort(long[],long);

int main()
{
 long array[1000],i,n;

 printf("enter ur array number?\n");
 scanf("%d",&n);

 printf("enter ur array?\n");
 for(i=0;i<n;++i)
 {scanf("%d",&array[i]);}

 printf("bubble sort!\n");

 bubble_sort(array,n);

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




void bubble_sort(long list[],long n)
{

 long i,d,swap;

 for(d=0;d<(n-1);++d)
 {

 for(i=0;i<(n-d-1);++i)
 {
  if(list[i]>list[i+1])
  {
   swap=list[i] ;
   list[i]=list[i+1];
   list[i+1]=swap;
  }

 }

 }


}


