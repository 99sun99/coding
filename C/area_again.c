#include<stdio.h>

/*　int main(void)表示不接受参数，int main()表示授受任何数量的参数，void main()表示接受任何参数且无返回值。　　1、main() 老式的写法。返回类型int在新型的编译器不可省略，
否者会有警告；
　　2、int main(void) 新式的写法；
　　3、int main() 新式的写法；
　　4、void main() 老式、不标准的写法，6.0 之前的VC使用这样的写法；
   main()相当于int main()；*/
main()
{
    int x;
    printf("enter a number\n");
    scanf("%d",&x);//&!
    if  (x%2==0)// 2blocks after if
        printf("%d is even\n",x);//4 blocks
    else
        printf("%d is odd\n",x);
    return 0; //返回//
}
