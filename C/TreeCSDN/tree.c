#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <math.h>
#define NUM 6


typedef struct _node
{
	int value;

	struct _node *left;

	struct _node *right;
}TNode, *Tree;

//add a *next in q_node is my purpose
//other wise , we need to add in the Tree node struct
//So, for the sake of doesn't modify the struct of tree
//I design a q_node struct to include it
//we can use define command to make it as a template.
typedef struct _q_node
{
	TNode *t_node;
	int depth;
	int blank;  //0: means correspoinding tree node is not NULL(default)
	struct _q_node *next;
}QNode;

typedef struct _Queue
{
	QNode *head;
	QNode *tail;
}Queue;

Queue* init_queue()
{
	Queue *queue = (Queue*)malloc(sizeof(Queue));
	queue->head = queue->tail = NULL;
	return queue;
}

int enQueue(Queue *pQueue, TNode *pTNode, int pDepth)
{

	QNode *pQNode = (QNode *)malloc(sizeof(QNode));
	pQNode->depth = pDepth;
	pQNode->blank = 0; //default config
	if (pTNode == NULL)
	{
		//change default setting; 1 means it's blank QNode
		pQNode->blank = 1;
	}

	pQNode->t_node = pTNode;

	if (pQueue->head == NULL && pQueue->tail == NULL)
	{//when it's empty
		pQueue->head = pQueue->tail = pQNode;
		pQueue->head->next = pQueue->tail->next = NULL;

	}
	else
	{
		pQueue->tail->next = pQNode;
		pQueue->tail = pQueue->tail->next;
		//pin the head and move the tail and let the head find the tail
		if (pQueue->head == NULL)
		{
			pQueue->head = pQueue->tail;
		}

	}

	return 0;
}

QNode* deQueue(Queue *pQueue)
{
	if (pQueue->head == NULL)
	{
		return NULL;
	}

	QNode *deNode = pQueue->head;


	pQueue->head = pQueue->head->next;


	return deNode;
}

//0:empty
int ifEmpty(Queue *pQueue)
{
	if (pQueue->head == NULL && pQueue->tail == NULL)
	{
		printf("empty tree\n");
		return 0;
	}

	printf("queue is not empty\n");
	return 1;
}


TNode* init_TNode(int value)
{
	TNode  *new_node = (TNode*)malloc(sizeof(TNode));
	new_node->value = value;
	new_node->left = new_node->right = NULL;
	return new_node;
}

int insert_tree(Tree pTree, int pValue)
{

	//found NULL sub tree, then add to his father->left
	if (!pTree)
	{
		return 0;
	}

	TNode *tNode = init_TNode(pValue);

	if (tNode == NULL)
	{
		printf("create TNode error!\n");
		return 0;
	}

	if (pValue < pTree->value)
		if (insert_tree(pTree->left, pValue) == 0)
		{
			//no left child any more,set a new left child to pTree
			pTree->left = tNode;
			printf("insert :%d\n", pValue);
		}
	if (pValue > pTree->value)
		if (insert_tree(pTree->right, pValue) == 0)
		{
			pTree->right = tNode;
			printf("insert :%d\n", pValue);
		}

	return 1;
}

Tree creatTree(int num)
{
	srand(time(NULL));
	Tree root = init_TNode(rand() % 100);
	printf("root is %d\n", root->value);
	int i;
	for (i = 1; i < num; i++)
	{
		insert_tree(root, rand() % 100);
	}
	printf("creat tree succuessfully!Tree heigh is:%d\n", get_tree_height(root));
	return root;
}

int get_tree_height(Tree pRoot)
{

	if (!pRoot)
	{
		return 0;
	}

	int lh = 0, rh = 0;
	lh = get_tree_height(pRoot->left);
	rh = get_tree_height(pRoot->right);

	return (lh < rh) ? (rh + 1) : (lh + 1);

}

int breath_travel(Tree pRoot, Queue *pQueue)
{
	int height = get_tree_height(pRoot);
	int total_node = pow(2, height) - 1;
	printf("##################################total node=%d################################\n", total_node);
	int count = 0;
	int pad_num = 3;
	//compare to the node's depth in the "while loop"
	int current_depth = 1;

	if (!pRoot)
	{
		return 0;
	}

	enQueue(pQueue, pRoot, 1);

	printf("_______________________\n");
	printf("breath begin,enter root:\n");
	//begin from zero so <, begin from 1 <=
	while (count < total_node)
	{
		//count++; //also ok!
		QNode  *qNode = deQueue(pQueue);
		if (qNode == NULL)
		{
			puts("error to dequeue");
			return -1;
		}
		//the sub node's depth is 1 more then the parent's
		int child_depth = qNode->depth + 1;//之前深度已经赋值1了，enQueue(pQueue,pRoot,1);这时候是输入第一层子树，即第二层,保证最后一行之后不再有新的，因为+1了，提早到达范围边界
		//current_depth&child_depth
		if (qNode->depth > current_depth)
		{
			current_depth = qNode->depth;
			printf("\n\n");
		}
		// ***************0****************  pad_between = 31 ; pad_front = 15  (depth == 1)  一共31个*
		// *******0***************0********  pad_between = 15 ; pad_front = 7   (depth == 2)    前面7后面8个星星
		// ***0*******0*******0*******0****  pad_between = 7  ; pad_front = 3   (depth == 3)
		// *0***0***0***0***0***0***0***0**  pad_between = 3  ; pad_front = 1   (depth == 4)
		// 0*0*0*0*0*0*0*0*0*0*0*0*0*0*0*0*  pad_between = 1  ; pad_front = 0;  (depth == 5)
		// Tree height = 5
		// pad_num = 1
		// padding between node = (1+2*pad_front)*pad_num = (1+ (1<<(height-depth))-1)*pad_num
		// (1<< (height - current_depth))-1=2^(height - current_depth)-1
		//1<<n n=0 pow(2,0)  n=m pow(2,m) 
		//找pow(2,m)  之间的关系描述树的结构
		//二进制常用变换

		int pad_front = (1 << (height - current_depth)) - 1;//最后一行=0倒推的式子！ 0=1<<0-1

		if ((qNode->blank == 1))
		{
			//add the parent node's padding:2
			if (pad_front == 0)    printf("%*s%*s", pad_num, "o", pad_num, " ");//此处pad_num=3，那么例如这个地方就是留了3个位置，两个空格和一个"o"
			//如果第一个数是四位，那么就是前三位+多一位，多一位后面重新开始归零计算，这样会不齐，比如creatTree 里面把rand()%100变成rand()%100000000不齐的会很明显
			//所以最好根据预估的位数，计算设置相应的pad，打印才会整齐
			//100是三位数所以pad_num设置成3
			//printf("%*s", 10, s); 意思是输出字符串s，但至少占10个位置，不足的在字符串s左边补空格，这里等同于printf("%10s", s);
			//左边不是右边加空格是因为有开头是数字的0padding的最后一组情况
			else                  printf("%*s%*s%*s", pad_front*pad_num, " ", pad_num, "o", (1 + pad_front)*pad_num, " ");
			//pad_num is the basic unit for padding, pad_front means the number of pad_num
			//pad_front*pad_num+(1+pad_front)*pad_num=(1+2*pad_front)*pad_num=padding between node
			//or pad_front*pad_num+pad_num=(1 + pad_front)*pad_num  
			//decide how many padding numbers for one group

			if (child_depth <= height)
			{
				//enter two NULL sub-tree node.
				//every time you enter NULL TNode,there's corresponding blank QNode.
				enQueue(pQueue, NULL, child_depth);
				enQueue(pQueue, NULL, child_depth);
			}
		}

		else
		{
			if (pad_front == 0)   printf("%*d%*s", pad_num, qNode->t_node->value, pad_num, " ");
			else                 printf("%*s%*d%*s", pad_front*pad_num, " ", pad_num, qNode->t_node->value, (1 + pad_front)*pad_num, " ");
			if (child_depth <= height)
			{
				enQueue(pQueue, qNode->t_node->left, child_depth);
				enQueue(pQueue, qNode->t_node->right, child_depth);
			}
		}

		count++;
		free(qNode);
	} //while end


	printf("\n-----------\nbreath end!\n-----------\n");

	return 1;
}

TNode * searchBinSearchTree(TNode * t, int find)
{
	while (t)
	{
		if (t->value == find)
			return t;
		else if (find > t->value)
			t = t->right;
		else
			t = t->left;
	}
	return NULL;
}

TNode* getParentBinSearchTree(TNode *root, TNode *t)
{
	static TNode *parent = NULL; 

	if (root)
	{
		if (root->left == t || root->right == t)
			parent = root;

		getParentBinSearchTree(root->left, t);
		getParentBinSearchTree(root->right, t);
	}

	


	return parent;
}

TNode *getMinNodeBinSearchTree(TNode * r)
{
	if (r)
	{
		while (r->left)
		{
			r = r->left;
		}
		return r;
	}
	return NULL;
}
TNode *getMaxNodeBinSearchTree(TNode * r)
{
	if (r)
	{
		while (r->right)
		{
			r = r->right;
		}
		return r;
	}
	return NULL;
}