#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#define NUM 10

typedef struct _node
{
   int value;
   int total_node;


   struct _node *left;
   struct _node *right;

}TNode,*Tree;

//add a *next in q_node is my purpose
//other wise , we need to add in the Tree node struct
//So, for the sake of doesn't modify the struct of tree
//I design a q_node struct to include it
//we can use define command to make it as a template.
typedef struct _q_node
{
  TNode *t_node; //为了给tnode加个next功能，，单独加的形式再次

 //TNode *t_nodespace;
 long  length;//for space

  struct _q_node *next;
}QNode;

typedef struct _Queue
{
   QNode *head;
   QNode *tail;
}Queue;

Queue* init_queue()
{
   Queue *queue=(Queue*)malloc(sizeof(Queue));
   queue->head = queue->tail = NULL;
   return queue;
}

int enQueue(Queue *pQueue,TNode *pTNode)
{

      QNode *pQNode = (QNode *)malloc(sizeof(QNode));
      pQNode->t_node = pTNode;
	  pQNode->next = NULL;
	  


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
}

QNode* deQueue(Queue *pQueue) //返回的值有q_node的结构 有next
{
	if(pQueue->head == NULL)
	{
	   return NULL;
	}

	QNode *deNode= pQueue->head;

	pQueue->head = pQueue->head->next; //如果是null 就重新enqueue下面是队列
	//pQueue->head=pQueue->head+1;
        return deNode;
}

TNode* init_TNode(int value)
{
    TNode  *new_node = (TNode*)malloc(sizeof(TNode));
    //TNode  *new_node = (Tree)malloc(sizeof(TNode));
    new_node->value=value;
    new_node->left = new_node->right = NULL;
    return new_node;
}

//0:empty
int ifEmpty(Queue *pQueue)
{
   if(pQueue->head == NULL)
   {
     //printf("empty tree\n");
     return 0;
   }

   //printf("queue is not empty\n");
   return 1;
}


int insert_tree(Tree pTree,int pValue, int *n)
//int insert_tree(TNode *pTree,int pValue)
{

   //found NULL sub tree, then add to his father->left
   if(!pTree)
   {
      return 0;
   }
   TNode *tNode = init_TNode(pValue);
   if(tNode==NULL)
   {
       printf("create TNode error!\n");
       return 1;
   }


   if(pValue < pTree->value)
        if(insert_tree(pTree->left,pValue,n)==0)//不为零的时候循环到下一层
        {
	   //no left child any more,set a new left child to pTree
	   pTree->left = tNode;
	   (*n)++;
   	   printf("insert :%d\n",pValue);
	}
   if(pValue > pTree->value)
        if(insert_tree(pTree->right,pValue,n)==0)
        {
           pTree->right = tNode;
		   (*n)++;
	   printf("insert :%d\n",pValue);
        }
}



Tree creatTree()
{
    srand(time(NULL));
    // srand((unsigned)time(NULL)); //标准写法 seed rand,之后用rand()
    // 而time(NULL)这个函数的返回值是作为srand函数的参数的！意思是以现在的系统时间作为随机数的种子来产生随机数！至于NULL这个参数。只有设置成NULL才能获得系统的时间！

    Tree root = init_TNode(rand()%100);
    printf("root is %d\n",root->value);
    int i ;
	int n = 0;
    for(i=1;i<NUM;i++)
    {
		//printf("[%d]     ", i);
        insert_tree(root,rand()%100,&n);
		printf("n= %d\n", n);
    }

    printf("creat tree succuess!Tree heigh is:%d\n",get_tree_height(root));
	root->total_node = n;
    return root ;
}

int get_tree_height(Tree pRoot)
{

  if(!pRoot)
  {
    return 0;
  }

  int lh=0,rh=0;
  lh = get_tree_height(pRoot->left);
  rh = get_tree_height(pRoot->right);
  return (lh<rh)?(rh+1):(lh+1);
}

int breath_travel(Tree pRoot,Queue *pQueue)
{
	
	int count = 0;
	int total_node = pRoot->total_node;
	printf("total_node = %d \n", total_node);

   if(!pRoot)
   {
      return 0;
   }

   enQueue(pQueue,pRoot);//只指向第一块儿
   printf("_______________________\n");
   printf("breath begin,enter root:\n");

   while( count< total_node)
   {
	   count++;

     QNode  *qNode  = deQueue(pQueue);//pQueue指向下一块

     //make suer every enQueue Node is not NULL
     if(qNode->t_node->left!=NULL)//left不是空的时候
       {enQueue(pQueue,qNode->t_node->left);} //如果

      if(qNode->t_node->right!=NULL) //只着眼于当前块的左右排列
      {
          enQueue(pQueue,qNode->t_node->right);
      }  //先左后右，打印的顺序也是，这样就对应了，从左到右排成一个Queue之后打印也是从左到右

     //print the tree node value ，if it is not NULL
     printf("%d ",qNode->t_node->value);
	 free(qNode);

   }

   printf("\n-----------\nbreath end!\n-----------\n");

   return 1;
}


int main()
{
  Queue *queue=init_queue();
  int i;

  ifEmpty(queue);
  printf("insert node to queue\n");

  Tree root = creatTree();
  if(!root)
  {
    printf("create Tree failed!\n");
    return 0;
  }

  breath_travel(root,queue);
//  free(queue);
  return 0;
}
