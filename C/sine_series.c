#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>

int main()
{
    int i,n;
    float x,val,sum,t,a,b,c;

    printf("enter x\n");
    scanf("%f",&x);
    printf("enter n\n");
    scanf("%d",&n);

    //printf("x=%d, address=%d  \n",x,&x);
    /*
    val=x;
    x=x*3.14/180;
    t=x;
    sum=x;
    */
    //传参的正确方式
    val=x;
    printf("val=%f, address=%d  ",val,&val);
    x=x*3.14/180;
    printf("x=%f, address=%d  ",x,&x);
    t=x;
    printf("t=%f, address=%d  ",t,&t);
    sum=x;
    printf("sum=%f, address=%d  \n",sum,&sum);

    for(i=1;i<n+1;++i)
    {
        a=2*i-1 ;
        b=2*i+1 ;
        c=2*i ;

        printf("c= %f\n",c);

        //t = (t*pow((double)(-1),(double)(a))*x*x)/((double)(c*b)) ;
        t = (t*pow((-1),(a))*x*x)/((c*b)) ;

         printf("t= %20.20f \n",t);

        sum=sum+t ;


    }

    printf("\nsine value of %f is :%8.4f",val,sum);//八位，保留小数点后面四位，0.算两位，前面空两位



}


//https://www.codingconnect.net/c-program-sine-series/
// sine 0处展开 级数展开 因为x和inx通过级数直接相连
