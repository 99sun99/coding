#include<stdio.h>
#include<stdlib.h>
#include<math.h>
// c++? using namespace std;
/*void main表示函数没有返回值，而main则有返回值。
只不过给省略了而已！函数没有声明类型时默认是为整型的，
main等同于int main 。自定义函数时如果主函数用的是void main，
就不能使用return把值返回给主函数，会报错*/

//暂时先用这个 int main(void) return这个形式，其他的都没法返回0 目前看，怕有溢出什么的//


void main()
{
        int height,base;
        float ans;
        printf("enter the height & weight\n");
        scanf("%d %d",&height,&base);

        ans = height*base*(1.00/2.00);//默认整数，想要分数结果就要把分数上下同时乘除小数
        printf("Area of triangle is %.4lf",ans);//四位浮点表示方法

}
