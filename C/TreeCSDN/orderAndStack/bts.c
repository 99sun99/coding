#include <stdio.h>
#include <stdlib.h>

#include "C:\work\coding\C\orderAndStack\Header.h"
//#include "C:\work\coding\C\Stack.c"




void preOrderTraverase(TreeNode *r)
{
	Stack s;
	initStack(&s);

	while(r || !isStackEmpty(&s))
	{
		while(r)
		{ 
			printf("%d\t", r->_data);
			push(&s, r);
			r = r->_left;
		}

		if (!isStackEmpty(&s))
		{
			r = pop(&s);
			r = r->_right;
		}
	}
}

void midOrderTraverase(TreeNode *r)
{
	Stack s;
	initStack(&s);

	while (r||!isStackEmpty(&s))
	{
		while (r)
		{
			push(&s, r);
			r = r->_left;
		}

		if (!isStackEmpty(&s))
		{
			r = pop(&s);
			printf("%d\t", r->_data);
			r = r->_right;

		}
	}
}


void postOrderTraverase(TreeNode *t)
{
	Stack s;
	initStack(&s);

	TreeNode *cur;
	TreeNode *pre = NULL;

	push(&s, t);
	while (!isStackEmpty(&s))
	{
		cur = pop(&s);
		push(&s, cur);
		if ((cur->_left == NULL && cur->_right == NULL) || (pre != NULL && (pre == cur->_left || pre == cur->_right)))
		{
			printf("%d\t", cur->_data);
			pop(&s);
			pre = cur;
		}
		else
		{
			if(cur->_right !=NULL)
			{
				push(&s, cur->_right);
			}
			if(cur->_left != NULL)
			{
				push(&s, cur->_left);
			}
		}

	}
}





int main(void)
{
	TreeNode a, b, c, d, e, f;
	TreeNode * root = &a;
	a._data = 1;
	b._data = 2; c._data = 3;
	d._data = 4; e._data = 5; f._data = 6;
	a._left = &b;
	a._right = &c;
	b._left = &d;
	b._right = &e;
	c._left = NULL; c._right = &f;
	d._left = d._right = NULL;
	e._left = e._right = NULL;
	f._left = f._right = NULL;

	printf("先序遍历:");
	preOrderTraverase(root);

	printf("\n 中序遍历:");
	midOrderTraverase(root);

	printf("\n 后序遍历:");
	postOrderTraverase(root);

	return 0;
}