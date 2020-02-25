#include<stdio.h>
#include<stdlib.h> //P72 C P21 C++
#include<math.h>

long factorial(int);//not void, should be identical with the argument below
long find_npr(int,int);//long nest(int) int in the long  we declare it first
long find_ncr(int,int);// global function declare global



int main()
{
int n,r;// need to be input next so declare first
long ncr,npr;/* more bits,use variables at the beginning of a
block (temporarily) to help track down
problems.*/

printf("enter n & r\n");
scanf("%d %d",&n,&r);//if unknowingly error occurs find the right path

ncr=find_ncr(n,r);//exactly arguments n,r
npr=find_npr(n,r);//slightly expressed

printf("ur ncr is %ld ",ncr);
printf("\nur npr is %ld",npr);

return 0;
}


long find_ncr(int n,int r)
{

 long result;// define it every time
 result = factorial(n)/(factorial(r)*factorial(n-r));// too many arguments maybe false from beginning factorial(void) was wrong
 return result;//return to be used by others

}



long find_npr(int n,int r) //beginning to declare the type
{
 long result; //char result is also ok, this is the locally define if it isn't mentioned it will be used still
 result = factorial(n)/factorial(n-r);
 return result;//The scope of a local variable is limited to the function

}


long factorial(int n)
{
 int c; // locally
 long result=1;// must be a initiative number!!!!!!!!!!!!
 for (c=1;c<=n;++c)//for (c=1;c<=n;c++) c++ may equals to c itself,so ++C,don't need initial value for c

  result=result*c;// c=1 is the beginning, incremental stuff needs to be activated
  //c=++c;

 return(result);

}
/*for ( initial; condition; increment )
statement;

while (count <= 20)
{
printf(“%d\n”, count);
count++;
}
mostly,we use increment in for nest. we use while to calculate in the statement
*/

