#include <stdio.h>


int main()

{
    char array[100];

    printf("enter a string!\n");
    scanf("%s",array);

    printf("ur string is %s\n",array);

    return 0;
}



/*
int check_vowel(char);

int main()
{
  char s[100], t[100];
  int i, j = 0;

  printf("Enter a string to delete vowels\n");
  gets(s);

  for(i = 0; s[i] != '\0'; i++) {
    if(check_vowel(s[i]) == 0) {       //not a vowel
      t[j] = s[i];
      j++;
    }
  }

  t[j] = '\0';

  //strcpy(s, t);    //We are changing initial string

  printf("String after deleting vowels: %s\n", t);

  return 0;
}


int check_vowel(char c)
{
  switch(c) {
    case 'a':
    case 'A':
    case 'e':
    case 'E':
    case 'i':
    case 'I':
    case 'o':
    case 'O':
    case 'u':
    case 'U':
      return 1;
    default:
      return 0;
  }
}



*/

/*
int main()
{
    char a[1000];
    char b[1000];

    //scanf("%s ",a);
    gets(a);//这种情况用gets用别的连不上
    strcpy(b,a);
    strcat(a,b);
    strrev(b);

    printf("a=%s b=%s\n",a,b);
    printf("strcmp %d",strcmp(a,b));

    return 0;
}

*/

/*
int main()
{
 int m,n ,o,p;

   m=1;
   o=++m;
   printf("o=%d\n",o);//o赋值了
   n=1;
   p=n++;
   printf("p=%d\n",p);



 return 0;
}

*/

/*
int main()
{
 int m,n ,o,p;

   for(m=0;m<=10;++m)
   {


   }
   o=++m;
   printf("o=%d\n",o);//o赋值了

   for(n=0;n<=10;n++)
   {

   }

   p=n++;
   printf("p=%d\n",p);



 return 0;
}

*/

/*

int check_vowel(char);

int main()
{
    char a[1000];
    char b[1000];
    int i,j=0;

    puts("enter ur string");
    gets(a);


    for(i=0;a[i]!='\0';++i)
    {
        if(check_vowel(a[i])==0)
        {
            b[j]=a[i];
            ++j;

        }

    }


    //b[]='\0';

    printf("after deleting %s",b);

    return 0;
}


int check_vowel(char c)  //返回 int
{
  switch(c)
  {
     case'a':
     case'e':
     case'i':
     case'o':
     case'u':
     case'A':
     case'E':
     case'I':
     case'O':
     case'U':
     return 1;
     default :
     return 0;


  }



}


*/


/*
int main()
{
char array[100];
//char a[]={'a','b','c'};
//char b[]={'a','b','c'};
char a[]="hello！";//有 []
char b[]="hello！";
int c[]={1,2,3};

int d;

scanf("%s",array);

//strcpy
//strcat
//strlen
//strlwr
//strupr
//strrev
//puts()  gets()
d=strcmp(a,b);
printf("%d",d);
printf("\n c[1]=%d",c[1]);

 return 0;
}

*/

/*

//输出string的几个方法的研究




int main( )
{
int count;

char *message[8] = { "Four", "score", "and", "seven","years", "ago", "our", "forefathers" } ;
//这样不行 char b[] = { "Four", "score", "and", "seven","years", "ago", "our", "forefathers" } ;
//21天 P426 FIGURE 15.4 原理 自动分配成a=&b的形式 只不过是倒回去的 图上写的很清楚 这种时候 一个字母占一位
//只能这样 char string[10] = { 'A', 'l', 'a', 'b', 'a', 'm', 'a','\0'};
char b[10] = { 'A', 'l', 'a', 'b', 'a', 'm', 'a','\0'};
int c[5]={1,2,3};

for (count = 0; count < 8; count++)
{printf("%d ", *message[count]);}
printf("\n");
for (count = 0; count < 8; count++)
{printf("%s ", message[count]);}
printf("\n");
for (count = 0; count < 8; count++)
{printf("%d ", &message[count]);}
printf("\n");

for (count = 0; c[count]!='\0'; count++)
{printf("%d ", c[count]);}
printf("\n");


for (count = 0; b[count]!='\0'; count++)
{printf("%d ", b[count]);}

printf("\n");
//因为作为数字可以直接输出 但是作为


printf("%d\n",message[3]);

printf("b[3]=%c",b[3]);
//没法输出词组，只能化成指针  实际上是数字的形式
//21天 P426 FIGURE 15.4 原理 自动分配成a=&b的形式 只不过是倒回去的
//就不用 char message[8] = "four score and seven years ago our forefathers "
//但是出来的是 four sco  这个时候一个字母变成一个元素，上面是告诉了多少个字母是一个元素


return 0;

}



*/

/*
总结
char a[]="it is a string!" ; //已经告诉他们了这个维度，就不写了
printf("%s",a);

char b[10] = { 'A', 'l', 'a', 'b', 'a', 'm', 'a','\0'};
printf("%s",b);

char *message[8]= { "Four", "score", "and", "seven","years", "ago", "our", "forefathers" } ;
for (count = 0; count < 8; count++)
{printf("%s ", message[count]);}
//P426 指向的是不带星号的，这里是一组char,用&是因为要指向地址  ，*间接指向地址，通过谁间接指向，用*




int c[]={1,2,3};
for (count = 0; count < 8; count++)
{printf("%d ", c[count]);}

int array[]={1,2,3,4,5};
printf("*array=%d  *(array+4)=%d addres=%d",*array,*(array+4),(array+4));


int (*ptr)[4] ；int *ptr [4]

一个指针指向四个元素的数组和后面一个有四个指针的数列


*/

/*
正负问题
int main( )
{
    char a[]="hello moto!";
    char b[10] = { 'A', 'l', 'a', 'b', 'a', 'm', 'a','\0'};
    strcmp(a,b);
    printf("%d",strcmp(b,a));
    printf("%d",strcmp(a,b));

return 0;

}

*/

/*
int main()
{
char a[]="hello~";
char b[]={'u','a','r','e','m','i','n','e','\0'};
char *c[3]={"you","are","cute"};//含着一位 ‘\0’ ？
char d[1000];
int i;


printf("%s\n",a);
//puts(b);
//puts(c);
printf("%s\n",b);

//for(i=0;c[i]!='\0';i++)

for(i=0;i<3;i++)
{
    printf("%s ",c[i]);
}


printf("\nenter ur word\n");
scanf("%s",d);
puts(d);


    return 0;
}




*/

