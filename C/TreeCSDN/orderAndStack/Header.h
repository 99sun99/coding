#ifndef  _MY_STACK_
#define  _MY_STACK_

typedef struct _TreeNode
{
	int _data;
	struct _TreeNode *_left;
	struct _TreeNode *_right;
}TreeNode;



typedef struct _SNode
{
	TreeNode *_data;
	struct _SNode *_next;
}SNode;



typedef struct _Stack
{
	SNode  *top;
}Stack;




#endif