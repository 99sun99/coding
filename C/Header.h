#pragma once
#ifndef  _MY_STACK_
#define  _MY_STACK_


typedef struct _SNode
{
	char _data;
	struct _SNode * _next;
}SNode;

typedef struct _Stack
{
	SNode * top;
}Stack;

void initStack(Stack * ps)
{
	ps->top = NULL;
}
int isStackEmpty(Stack * ps)
{
	return ps->top == NULL;
}
void push(Stack *ps, char ch)
{
	SNode * cur = (SNode *)malloc(sizeof(SNode));
	cur->_data = ch;
	cur->_next = ps->top;
	ps->top = cur;
}
char pop(Stack *ps)
{
	SNode * t = ps->top;
	char ch = t->_data;
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






#endif