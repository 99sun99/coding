#include<stdio.h>

int main()
{
int x,y,temp;
printf("enter x and y\n");
scanf("%d %d",&x,&y);
printf("x=%d y=%d\n",x,y);

temp=x;//way to change parameter
x=y;
y=temp;
printf("x=%d y=%d\n",x,y);

return 0;
}
