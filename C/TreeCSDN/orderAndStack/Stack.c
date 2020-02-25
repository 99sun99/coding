#include <stdio.h>
#include <stdlib.h>
#include "C:\work\coding\C\orderAndStack\Header.h"



void initStack(Stack * ps)
{
	ps->top = NULL;
}
int isStackEmpty(Stack * ps)
{
	return ps->top == NULL;
}

void push(Stack *ps, TreeNode *r)
{
	SNode * cur = (SNode *)malloc(sizeof(SNode));
	cur->_data = r;
	cur->_next = ps->top;
	ps->top = cur;
}

TreeNode* pop(Stack *ps)
{
	SNode * t = ps->top;
	TreeNode *ch = (TreeNode*)malloc(sizeof(TreeNode));
	ch=t->_data;
	ps->top = ps->top->_next;
	free(t);
	return ch;
}

void clearStack(Stack * ps)
{
	SNode * t;
	while (ps->top)
	{
		t = ps->top;
		ps->top = ps->top->_next;
		free(t);
	}

}


