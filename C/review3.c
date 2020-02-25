#include <stdio.h>
#include <stdlib.h>

#include "C:\work\coding\C\orderAndStack\Header.h" 
//#include "C:\work\coding\C\orderAndStack\Stack.c" 



void preOrderTraverase(TreeNode *root)
{
	Stack s;
	initStack(&s);



	while (root||!isStackEmpty(&s))
	{
		while (root)
		{
			
			printf("%d\t", root->_data);
			push(&s, root);			
			root = root->_left;
		}
		if (!isStackEmpty(&s))
		{
			root = pop(&s);
			root = root->_right;
		}
	}
}


void midOrderTraverase(TreeNode *root)
{
	Stack s;
	initStack(&s);

	while (root || !isStackEmpty(&s))
	{
		while (root)
		{
			push(&s, root);
			root = root->_left;
		}
		if (!isStackEmpty(&s))
		{
			root = pop(&s);
			printf("%d\t", root->_data);
			root = root->_right;
		}
	}
}


void postOrderTraverase(TreeNode *root)
{
	Stack s;
	initStack(&s);
	TreeNode *pre=NULL, *cur=NULL;
	push(&s, root);


	while (!isStackEmpty(&s))
	{
		cur = pop(&s);
		push(&s, cur);

		if((cur->_left==NULL&&cur->_right==NULL)||(pre!=NULL&&(cur->_left==pre || cur->_right==pre)))
		{ 
			printf("%d\t", cur->_data);
			pop(&s);
			pre = cur;
		}
		else
		{
			if (cur->_right != NULL)
				push(&s, cur->_right);
			if (cur->_left != NULL)
				push(&s, cur->_left);
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