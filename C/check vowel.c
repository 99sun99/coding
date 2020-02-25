#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main()
{
int reply;
puts("Enter a number between 1 and 5:");
scanf("%d", &reply);


switch (reply)
{
case 1:
puts("You entered 1.");//puts =printf
case 2:
puts("You entered 2.");// omit the middle description is ok
break;// any stop to explicitly programme ur need
case 3:// between entered word and the last one
puts("You entered 3.");
case 4:// 4 means reply value
puts("You entered 4.");
break;// stop the loop

default:
 puts("Out of range, try again.");

}

// puts("yep");//no default just closest  to the brace
/*puts(“Hello, world.”);
performs the same action as
printf(“Hello, world.\n”);
but puts() can’t display numeric variables.

case 'AEIOU':  (NEED '' )
puts("You entered aeiou.");

*/

return 0;

}
