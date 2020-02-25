#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <stdbool.h>
//C:\\work\\coding\\C\\test.txt




int main()
{
	FILE *fp = fopen("C:\\work\\coding\\C\\test.txt", "r+");
	if (fp == NULL)
	{
		return -1;
	}
	int lineCount=0;
	int len;
	char buff[1024];

	while (fgets(buff, 1024, fp) != NULL)
	{
		lineCount++;
	}
	rewind(fp);

	char **p = (char**)malloc((lineCount + 1) * sizeof(char*));
	char **pt=p;


	while (fgets(buff, 1024, fp) != NULL)
	{
		len = strlen(buff);
		*pt = (char*)malloc(len + 1);
		//*pt = buff;
		strcpy(*pt, buff);
		pt++;

	}

	*pt = NULL;//wild pointer problem

	while (*p)
	{
		printf("%s", *p);
			*p++;
	}

	fclose(fp);
	return 0;
}
