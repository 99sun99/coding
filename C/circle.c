/*#define s "12345" // 这是字符串
#define PI 3.1425927 // 这是double类型常量 (推算出圆周率的值在3.1415926和3.1425927之间)
#define N 10 // 这是int类型常量*/

#include<stdio.h>
#include<math.h>
#define PI 3.1425927

int main()
{

float radius,area;

printf("enter ur reduis\n");
scanf("%f",&radius);

area=PI*pow(radius,2);

printf("ur area is %10.2f",area);// leave 10blocks 2of them are fractional part 2include dot eg ans=314.62,4blocks left

return 0;

}

