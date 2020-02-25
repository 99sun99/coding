#include <stdio.h>
#include <stdlib.h>
#include <math.h>


// switch 练习 公约数算法 空间换时间 把每个数的质因数分解都标出来，到时候直接核对
// 这个跟人脑工作原理有点像，可是计算机没有灵感这个东东啊？
/*
int main()
{
    int ch;
    printf("enter ur word ?\n");
    scanf("%c",&ch);

    switch(ch)
    {
    case 'a':
    case 'A':
    printf("this is a or A");
    break;

    default:
    printf("normal");


    }

    return 0;



}
*/

//类型规定成ouble才能算，精度高，最后输出考虑位数，但是没有全部都算进去，有位数没显示
double factorial(int);

int main()
{
    int n;
    double m;
    printf("enter ur number\n");
    scanf("%d",&n);

    m=factorial(n);
    printf("%d !=%f",n,m);

    return 0;

}


double factorial(int a)


{
    int i;
    double sum=1;

    if(a!=0) //cannot nest while here because no trend for a
    {

    for(i=1;i<=a;++i)
    {
       sum=sum*i;

    }

    }

    else
    {
        sum=a;
    }


return sum;

}

/*

long long factorial(long);

int main()
{
    long n;
    long m;
    printf("enter ur number\n");
    scanf("%d",&n);

    m=factorial(n);
    printf("%d !=%ld",n,m);

    return 0;

}


long long factorial(long a)


{
    int i;
    long sum=1;

    if(a!=0)
    {

    return(a*factorial(a-1));

    }
    else
    {
        return 1;
    }




}


*/


/*
传了过多的参数了

int main()
{
    int i,n,a,b,c;
    float x,val,sum,t;

    printf("enter x\n");
    scanf("%d",&x);
    printf("enter n\n");
    scanf("%d",&n);


    val=x;
    x=x*3.14/180;
    t=x;
    sum=x;

    for(i=1;i<n+1;++i)
    {
        a=2*i-1 ;
        b=2*i+1 ;
        c=2*i ;

        printf("%d",c);

        t = (t*pow((double)(-1),(double)(a))*x*x)/((double)(c*(b))) ;

        sum=sum+t ;


    }

    printf("\nsine value of %f is :%8.4f",val,sum);



}

*/

/*

//shape!
int main()
{
    int i,a,b,c,d,n;
    printf("row?");
    scanf("%d",&n);
c=n;

for(i=1;i<=n;++i)
{
    for(a=1;a<c;++a)
    {printf(" ");}

    --c;
    //d=2*i-1;
    //for(b=1;b<=d;++b)
    for(b=1;b<=2*i-1;++b)
    {
        printf("*");
    }

    printf("\n");

}

   return 0;
}

*/
