#include<stdlib.h>
#include<stdio.h>
#include<string.h>


struct time {
int hours;
int minutes;
int seconds;
} time_of_birth = { 8, 45, 0 };




int main()
{



    printf("%d:%d:%d",time_of_birth.hours,time_of_birth.minutes,time_of_birth.seconds);


return 0;

}

