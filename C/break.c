/* Demonstrates the break statement. */
#include<stdlib.h>
#include <stdio.h>

char s[] = "This is a test string. It contains two sentences.";

int main( void )
{
int count;

printf("\nOriginal string: %s", s);

for (count = 0; s[count]!='\0'; count++) // \0 programme think the string is over,字符串查找程序，如果最后不是结束


if (s[count] == '.')
{
s[count+1] = '\0'; //if it is a period
break;
}

printf("\nModified string: %s\n", s);

return 0;
}
