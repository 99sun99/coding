#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int check_prime(int);

int main()
{
 int i,n,result;

 printf("enter ur number\n");
 scanf("%d",&n);
 printf(" %d contains  prime numbers are :\n",n);

 for (i=0;i<=n;++i)
 {
 result=check_prime(i);

 //if(result==1&&i!=0) // only pick up needed situation

 if(result==1)
 printf("%d\n",i);


/*else
printf("0 is not a natural number\n");

*/


 }
 return 0;

}

int check_prime(int a) // a means i
{
 int c;
//for(c=2;c<a-1;++c)// only one number

for(c=2;c<=a-1;++c)// number list
{
// printf("before c is %d \n",c);//不重要
if(a%c==0)
//printf("a=%d c=%d is non prime\n",a,c);//不重要
return 0;// 只要有被整除的返回0，不算了，比如4，发现2马上不算了

}

//if(a==c)    //contain 1 because a从01开始，%0=0所以只有1
//if (a%c==0) //contain 1 because 1 is not under the for condition so jump here

if(c==a) //c==i big circle and small circle,2  情况单独拿出来 c begins with c=2 ,end with a-1,when ++c, increase to c==a
//printf("a=%d c=%d yep\n",a,c); // 很重要 ，可以看出来，只有上面循环都通过了全都没有整除的才会得到最后一步，就是它自己c==a 就是素数的结论
return 1;//比如13 从2-12都没有整除，才会落出来

//筛选思路


}


//another
/*

long prime(int);

int main()

{
 int m;
    printf("enter ur bits?\n");
    scanf("%d",&m);

    printf(prime(m));

  return  0;

}


long prime(int n)
{
int i;

 for(i=2;i<=n-1;++i)
 {
     if(n%i==0)
     printf("not prime");

     break;

 }

 if( n==i)
 printf("prime!");




}
*/










