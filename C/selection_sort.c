#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void selection_sort(long[],long);

int main()
{
 long array[1000],i,n;

 printf("enter ur array number?\n");
 scanf("%d",&n);

 printf("enter ur array?\n");
 for(i=0;i<n;++i)
 {scanf("%d",&array[i]);}

 printf("selection sort!\n");

 selection_sort(array,n);

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




void selection_sort(long list[],long n)
{

 long i,d,c,swap;

 for(d=0;d<(n-1);++d)
 {
   i=d;

  for(c=d+1;c<n;++c)//在后半段找最小
  {

  if(list[i]>list[c])
  i=c;//不停的把I 变成小的寄存器，保证一次出来最小，找最小

  }

  if(i!=d) //只要不是当前最小就换
   {
    swap=list[d];
    list[d]=list[i];
    list[i]=swap;
   }
  }



 }






