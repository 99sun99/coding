#include<stdio.h>

int main()
{
 int n,i ;//maximum=100
 long array[1000];

 printf("how many numbers u want to enter? \n");
 scanf("%d",&n);  // tap with block 2 5 6 7 reverse=7652

 printf("enter ur number\n");

for(i=0;i<n;++i) //for(begin=xxx,end,increment)
scanf("%ld",&array[i]); //array[i]


printf("reverse is :");

for(i=n-1;i>=0;--i) //use i to reverse,>=vs= different

printf("%ld",array[i]);

return 0;

}

/*

long reverse(int);

int main()

{
 int m;
    printf("enter ur bits?\n");
    scanf("%d",&m);

    printf(reverse(m));

  return  0;

}


long reverse(int n)
{
    long arrary[1000];
    int i;


    for(i=0;i<n;++i)
    {scanf("%ld",&arrary[i]);}

    printf("ur reverse is :");

    for(i=n-1;i>=0;--i)
    {printf("%ld",arrary[i]);}

    return 0;
}


*/


