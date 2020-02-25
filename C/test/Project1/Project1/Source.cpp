#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#define TBLSIZ 11

int main()
{
	int *a;
	int b = 2;

	a = &b;

	printf("%d", *a);


	return 0;
}
