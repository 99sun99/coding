
int main()
{
int i,a,b,c,d;

a=2^1;b=2&1;c=2|1;

//a=1^2;b=1&2;c=1||2;

        printf("%d %d %d ", a,b,c);


return 0;
}

/*
https://wenku.baidu.com/view/8bb52ffb700abb68a982fbba.html

	a ^= b;
	a=a^b
        b ^= a;
	b=b^a=b^a^b=a
        a ^= b;
	a=a^b=a^b^a=b
*/

/*

int main()
{
int i,a,b,c,d;
a=0;
for(i=1;i<101;i++)
{
 a^=i;
}

printf("%d",a);

return 0;
}


*/
