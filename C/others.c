#include<stdlib.h>
#include<stdio.h>
#include<string.h>


//测试 dir *.txt
int main( void )
 {

char input[40];
//gets(input);//放这里会无限循环

while (1)
 {


puts("\nInput the desired system command, blank to exit?");
gets(input);//必须循环在里面，在外面就没完了

if (input[0] =='\0')
{
    //puts("error");//退出机制不用写
    exit(0);//设置认为的结束不是自动的，1也行，不过返回的就是1了
}

 system(input);//dos 入口
 }
 return 0;
 }


/*
int main()
{
system("PAUSE");
return 0;
}


*/

/*
int main()
{
int ch;
while ((ch = getchar()) != '\n')
putchar(ch);


return 0;
}


*/


/*
struct  {
int x;
int y;
} coord;




int main()
{

    //struct  coord;



    //list=(struct init *)malloc(sizeof(list));

    coord.x=3;

    printf("%d",coord.x);

    return 0;


}



*/


/*
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

int main()
{
    FILE *fp;
    char ch,filename[40],mode[4];

    while(1)//只能认为break了
    {
        printf("enter ur filename\n");
        gets(filename);
        printf("enter a mode less than 3 char\n");
        gets(mode);

        if ((fp=fopen(filename,mode))!=NULL) //不能写"x"，'的类型不能超过四个字符，int会报错'
        //用单引号引起的一个字符实际上代表一个整数，整数值对应于该字符在编译器采用的字符集中的序列值
        {

            printf("successfully entered\n");
            fclose(fp);
            puts("enter 'x' to exit,any other to continue");
            if((ch=getc(stdin))=='x')
            {
                break;
            }
            else
            {
                continue;//继续循环
            }

        }

        else
        {
            fprintf(stderr,"\nerror opening file %s in mode %s\n",filename,mode);
            puts("enter 'x' to exit,any other to continue");
             if((ch=getc(stdin))=='x')
            {
                break;
            }
            else
            {
                continue;//继续循环
            }



        }


    }



    return 0;
}


*/

/*
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

void clear_kb(void);

int main()
{
    FILE *fp;
    float data[5];
    int count;
    char filename[20];

    puts("enter 5 floating-point number");

    for(count=0;count<5;count++)
    {
        scanf("%f",&data[count]);

    }

    clear_kb();

    puts("enter a file name");
    scanf("%s",filename);

    if((fp=fopen(filename,"w"))==NULL)
    {
        fprintf(stderr,"error opening %s",filename);
        exit(1);

    }

    for(count=0;count<5;count++)
    {
        fprintf(fp,"\ndata[%d]=%f",count,data[count]);
        fprintf(stdout,"\ndata[%d]=%f",count,data[count]);

    }

fclose(fp);
printf("\n");
return 0;



    return 0;

}
void clear_kb(void)
{
    char junk[100];
    gets(junk);

}




*/


/*
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

void clear_kb(void);

int main()
{
    FILE *fp;
    float data[5],copy[5];
    int count;
    char filename[20];

    puts("enter 5 floating-point number");

    for(count=0;count<5;count++)
    {
        scanf("%f",&data[count]);

    }

    clear_kb();

    puts("enter a file name");
    scanf("%s",filename);

    if((fp=fopen(filename,"w"))==NULL)
    {
        fprintf(stderr,"error opening %s",filename);
        exit(1);

    }

    for(count=0;count<5;count++)
    {
        fprintf(fp,"\ndata[%d]=%f",count,data[count]);
        fprintf(stdout,"\ndata[%d]=%f\n",count,data[count]);


    }




fclose(fp);
printf("\n");
return 0;



    return 0;

}
void clear_kb(void)
{
    char junk[100];
    gets(junk);

}

*/

/*

int main()
{
    float f1,f2,f3,f4,f5;
    FILE *fp;

    if((fp=fopen("junk.txt","r"))==NULL)
    {
        fprintf(stderr,"error\n");
        exit(1);
    }
    fscanf(fp," %f %f %f %f %f",&f1,&f2,&f3,&f4,&f5);

    printf("the values are %f %f %f %f %f",f1,f2,f3,f4,f5);


    fclose(fp);
    return 0;
}

*/


/*
struct kilo
{
    struct kilo *next;
    char dummy[1020];

};
int FreeMem(void);



int main()
{
    printf("You have %d kilobytes free.\n", FreeMem());


    return 0;
}

int FreeMem(void)
{

    long counter;
    struct kilo *head, *current, *nextone;

    current = head = (struct kilo*) malloc(sizeof(struct kilo));

    if (head == NULL)
    return 0;

    counter = 0;
    do
{
counter++;

current->next = (struct kilo*) malloc(sizeof(struct kilo));
current = current->next;
//printf("\r%d",counter);
} while (current!=NULL);

current = head;


do
{
nextone = current->next;
free(current);
current = nextone;
 } while (nextone != NULL);


return counter;
}

*/

/*
#define BUFLEN 6 //有一位是'\0'

char msg[]="abcdefghijklmnopqrstuvwxyz";

int main(void)
{
    FILE *fp;
    char buf[BUFLEN];

    if((fp=fopen("junk.txt","w"))==NULL)
    {

        fprintf(stderr,"error");
        exit(1);

    }

    if(fputs(msg,fp)==EOF)
    {
         fprintf(stderr,"error");
        exit(1);
    }

    fclose(fp);

    if((fp=fopen("junk.txt","r"))==NULL)

    {
         fprintf(stderr,"error");
        exit(1);
    }

    printf("\n immediately after opening postition =%ld\n",ftell(fp));

    fgets(buf,BUFLEN,fp);
    printf("\nafter reading %s ,postition =%ld\n",buf,ftell(fp));

    fgets(buf,BUFLEN,fp);
    printf("the next 5 chars are %s  ,postition =%ld\n",buf,ftell(fp));

     rewind(fp);
     printf("\n after rewind postition =%ld\n",ftell(fp));

     fgets(buf,BUFLEN,fp);

     printf("starts from  %s  ,postition =%ld\n",buf,ftell(fp));

     fclose(fp);






    return 0;
}


*/

/*
int main()
{

    FILE *fp;
    int data, count,array[MAX];
    long offset;

    for(count=0;count<MAX;count++)
    {
        array[count]=count*10;

    }

    if((fp=fopen("junk.txt","wb"))==NULL)
    {
        fprintf(stderr,"error opening file\n");
        exit(1);
    }

    if((fwrite(array,sizeof(int),MAX,fp))!=MAX)
    {
        fprintf(stderr,"error writing\n");
        exit(1);
    }

    fclose(fp);

    if((fp=fopen("junk.txt","rb"))==NULL)
    {

        fprintf(stderr,"error opening");
        exit(1);
    }



    while(1)
    {
        printf("\nenter 0-%d,-1 to quit:",(MAX-1));
        scanf("%ld",&offset);

        if(offset<0)
        {
            break;
        }

        else if (offset>MAX-1)
        {
            continue;
        }

        if((fseek(fp,(offset*sizeof(int)),SEEK_SET))!=0)
        {
            fprintf(stderr,"\nerror using seek_set");
            exit(1);
        }

        fread(&data,sizeof(int),1,fp);
        printf("\n element %ld has value %d",offset,data);





    }

    fclose(fp);



    return 0;
}


*/

/*
#define BUFSIZE 100


int main()
{
    char buf[BUFSIZE];
    char filename[60];
    FILE *fp;

    puts("enter name of text file to display");
    gets(filename);

    if((fp=fopen(filename,"r"))==NULL)
    {

        fprintf(stderr,"error\n");
        exit(1);

    }

    while(!feof(fp))
    {
        fgets(buf,BUFSIZE,fp);
        printf("%s",buf);


    }

    fclose(fp);



    return 0;
}
*/

/*


int main()
{
  char filename[80];

  printf("enter name to delete\n");
  gets(filename);

  if(remove(filename)==0)
  {
      printf("the %s has been deleted",filename);
  }


    else
    {
        fprintf(stderr,"error deleting");


    }



    return 0;
}

*/

/*

int main()
{
    char oldname[80],newname[80];

    puts("enter current name");
    gets(oldname);
    puts("enter new name");
    gets(newname);

    if(rename(oldname,newname)==0)
    {printf("%s has been renamed as %s",oldname,newname);

    }

    else
    {


        fprintf(stderr,"an error occured when renaming %s",oldname);

    }

    return 0;
}

*/

/*

int file_copy(char *oldname, char *newname);

int main()

{
    char source[80],destinnation[80];

    printf("\nenter source file\n");
    gets(source);
    printf("\nenter destination file");
    gets(destinnation);

    if(file_copy(source,destinnation)==0)
    {
        puts("successful");
    }
    else
    {
        fprintf(stderr,"error");

    }




    return 0;
}

int file_copy(char *oldname, char *newname)
{
    FILE *fold, *fnew;
    int c;

    if((fold=fopen(oldname,"rb"))==NULL)
            {
                return -1;

            }
    if((fnew=fopen(newname,"wb"))==NULL)
    {
        fclose(fold);
        return -1;
    }


    while(1)
    {
        c=fgetc(fold);
        if(!feof(fold))
        {
            fputc(c,fnew);
        }
        else
        {
            break;
        }

    }

    fclose(fnew);
    fclose(fold);

    return 0;

}






*/

/*
int main()
{
    char buffer[10],*c;

    tmpnam(buffer);
    c=tmpnam(NULL);

    printf("temp name 1:%s\n",buffer);

    printf("temp name 2:%s\n",c);



    return 0;


}



*/

/*

typedef struct coord {
int x;
int y;
} first;
//} first,*a;
typedef  first *a;
int main()
{
    a b;
    b=(a)malloc(sizeof(first));
    (*b).x = 50;
    printf("%d",(*b).x);
    return 0;
}

*/

/*

struct coord {
int x;
int y;
} first;
//typedef  first *a;
int main()
{
    //a b;
    //b=(a)malloc(sizeof(first));
    first.x = 50;
    printf("%d",first.x);
    return 0;
}


*/






