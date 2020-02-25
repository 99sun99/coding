#include<stdlib.h>
#include<stdio.h>
#include<string.h>

 int lg(int);


int main()

{

     int i ,N;

     for(i=0,N=10;i<=6;i++,N*=10)
     {
         printf("N=%7d lgN=%2d N*lgN=%9d \n",N,lg(N),N*lg(N));
     }



   return 0;
}

 int lg(int N)
 {
     int i;
     for(i=0;N>0;i++,N/=2) ; //答案上取证

     return i;


 }


/*
//有问题

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<math.h>


int heads()
{
    return (rand()<(RAND_MAX/2));
}

 main (int argc,char *argv[])
{
    int i ,j ,cnt;
    int N=atoi(argv[1]),M=atoi(argv[2]);
    int *f=malloc((N+1)*sizeof(int));
    for(j=0;j<=N;j++) f[j]=0;
    for(i=0;i<M;i++,f[cnt]++)
       {
           for(cnt=0,j=0;j<=N;j++)
           {if(heads())
           cnt++;}
       }

    for(j=0;j<=N;j++)
    {
        printf("%2d",j);
        for(i=0;i<f[j];i+=10) printf("*");

        printf("\n");
    }



}

*/

/*
//这次全OK
int heads()
{
    return (rand()<(RAND_MAX/2));
}
 main (int argc,char *argv[])
{
    int i ,j ,cnt;
    int N,M;
    printf("Input N and M(like:2 2)\n");
    scanf("%d %d",&N,&M);
   // int N=atoi(argv[1]),M=atoi(argv[2]);
    int *f=malloc((N+1)*sizeof(int));

    for(j=0;j<=N;j++) {f[j]=0;}

    for(i=0;i<M;i++,f[cnt]++)
       {
           for(cnt=0,j=0;j<=N;j++)
           {if(heads())

           {cnt++;}}
       }
    printf("\nresult:\n");
    for(j=0;j<=N;j++)
    {
        printf("%2d",j);

        for(i=0;i<f[j];i+=1) printf("*");

        printf("\n");
    }
}
*/


/*

指针只能strcpy
struct list
{
    char filename[40];

    struct list *next_rec;
};

 struct list LIST[2];

int main()
{
    char ch[40]="yo yo ";
    int i;

    for(i=0;ch[i]!='\0';i++)
   {

    LIST[0].filename[i]=ch[i];
   }



    //strcpy(LIST[0].filename,ch);
    printf("%s",LIST[0].filename);


    return 0;

}



*/

/*


struct list
{
    int number;
    char name[40];


}data[4]={1,"tom",2,"jerry",3,"start",4,"yoyo"};

 struct list *LIST;

int main()
{
     LIST=data;
     int i;

     for(i=0;i<4;i++)
     {

         printf("the address is %d the number is %d the name is %s\n",LIST++,LIST->number,LIST->name);

     }





    return 0;

}
*/

/*
//直接用也行,但是必须把list 接着写
struct list
{
    int number;
    char name[40];



} LIST[4]={1,"tom",2,"jerry",3,"snoopy",4,"lit"};

//struct list LIST;

int main()
{
    int i;




    for (i=0;i<4;i++)
    {
        printf("number is %d name is %s\n",LIST[i].number,LIST[i].name);



    }






    return 0;
}
*/

/*
#include<stdlib.h>

int heads()
{

    return ((rand())<(RAND_MAX/2));
}


int main( )
{
    int M,N,i,j,cnt;
    char c;

    printf("enter M&N LIKE 2 2\n");

    scanf("%d %d",&M,&N);//空格要跟输入的一致哦！

   int *f=malloc((N+1)*sizeof(int));//不能先分配

    //*f=malloc((N+1)*sizeof(int));

    for(j=0;j<=N;j++) { f[j]=0;}

        printf("f[3]=%d\n",f[3]);


    for(i=0;i<M;i++,f[cnt]++)
    {

        for(cnt=0,j=0;j<=N;j++)
        {
            if(heads())
            {


                cnt++;

            }


        }
    }


    //getchar();
    //getchar();

     printf("\nresult:\n");

    for(j=0;j<=N;j++)
    {
         printf("%2d",j);

        for(i=0;i<f[j];i+=10) {printf("*");}

        printf("\n");
    }




    return 0;
}

*/

/*
#include<string.h>
//https://blog.csdn.net/qq_41750725/article/details/79947375


#define ElementType char  //定义 成char，跟 char A 作用一样。
struct StackNode
{
	ElementType data;
	int Length;
	struct StackNode* pNext;
};
typedef struct StackNode *Stack;

Stack CreateStack()
{
	Stack MyStack = (Stack)malloc(sizeof(struct StackNode));
	MyStack->pNext = NULL;
	MyStack->Length = 0;
	return MyStack;
}


void Push(Stack S,ElementType data)
{
	Stack TmpCell = (Stack)malloc(sizeof(struct StackNode));
	TmpCell->data = data;
	TmpCell->pNext = S->pNext;
	S->pNext = TmpCell;
}

ElementType Pop(Stack S)
{
	if (S->pNext==NULL)
	{
		printf("Empty\n");//S1 先PUSH的，不存在empty的问题
		exit(0);
	}
	Stack Temp;
	Temp = S->pNext;
	S->pNext = Temp->pNext;
	ElementType T = Temp->data;
	free(Temp);
	return T;
}
ElementType GetTop(Stack S)
{
	if (!S->pNext)
	{
		printf("Empty\n");
		exit(0);
	}
	Stack Temp;
	Temp = S->pNext;
	ElementType T = Temp->data;
	return T;
}

int main()
{
    	Stack S1 = CreateStack();
	char ch[20];
	printf("input parentheses number:\n");
	int n = 0;
	scanf("%d", &n);
	printf("input formula\n");
	scanf("%s", ch);
	int i = 0;
	char need;
	int flag = 0;
	for (i; i < n;i++)
	{
		switch (ch[i]) //有（）没有：
		{
		case '[':
		{
			need = ']';
			Push(S1, need);
			S1->Length++;
			break;
		}
		case '(':
		{
			need = ')';
			Push(S1, need);
			S1->Length++;
			break;
		}
		case ']':
		    {
				if (GetTop(S1) == ']')
				{
					ElementType T = Pop(S1);
					S1->Length--;
				}
				else
				{
					flag = 1;
				}
			        break;
		    }
		case ')':
		    {
				if (GetTop(S1) == ')')
				{
					ElementType T = Pop(S1);
					S1->Length--;
				}
				else
				{
					flag = 1;
				}
				break;//break 跳出switch
		    }
		default:
		    {
				  flag = 1;
			      break;
		    }
		}
	}

	if (S1->Length==0&&flag==0)
		printf("sucessfully\n");
	else
		printf("failed\n");
}


*/
/*
//C队列遍历基础
//改之前 https://blog.csdn.net/xzongyuan/article/details/21830097

#include<stdio.h>
#include<stdlib.h>

typedef struct _node //typedef
{
   int value;
   struct _node *next;
}Node;

typedef struct _Queue
{
   Node *head;  //NODE 不是 queue的，都是别人的指针集合
   Node *tail;//这样 queue就可以用node 的next指针和value了呀
}Queue;

Queue* init_queue()
{
   Queue *queue=(Queue*)malloc(sizeof(Queue));
   queue->head = queue->tail = NULL;
   return queue;
}

void enQueue(Queue *pQueue,Node *pNode)
{
      if(pQueue->head == NULL)
      {//when it's empty
           pQueue->head = pNode;
	   pQueue->tail = pNode;
      }
      else
      {
           pQueue->tail->next = pNode;//下一块儿
	   pQueue->tail = pNode;//还在当前块儿
      }
}

int deQueue(Queue *pQueue)
{
    int i;

	if(pQueue->head == NULL)
	{
	   return NULL;
	}
   // Node  *deNode;
   //Node *tmp;

	//Node  *deNode;
	//deNode= pQueue->head;
    Node  *deNode= pQueue->head;

	//Node *tmp= pQueue->head;

	i=deNode->value;

    pQueue->head= pQueue->head->next;

	free(deNode);

        return i;
}

Node* init_node(int value)
{
    Node  *new_node = (Node*)malloc(sizeof(Node));
    new_node->value=value;
    return new_node;
}

//0:empty
int ifEmpty(Queue *pQueue)
{
   if(pQueue->head == NULL)
   {
     printf("empty tree\n");
     return 0;
   }

   printf("queue is not empty\n");
   return 1;
}

int main()
{
  Queue *queue=init_queue();
  int i;

  ifEmpty(queue);
  printf("insert node to queue\n");
  for(i=0; i<7;i++)
  {
   Node *node = init_node(i);
   enQueue(queue,node);
  // free(node);
  }

//  Node *node = init_node(1);
//  printf("node->value = %d\n",node->value);
//  enQueue(queue,node);
  ifEmpty(queue);

  for(i=0;i<7;i++)
  {
	  int deNode = deQueue(queue);

	  //if(!deNode)
	  //{
	     //printf("NULL\n");
	  //}
	  //else
	  //{
	     printf("deNode->value = %d\n",deNode);

	  //}


  }

   //int deNode = deQueue(queue);
  //free(queue);

  // printf("\n after free deNode->value = %d\n",queue->head->value);//释放啦，只有地址没有别的啦


    //ifEmpty(queue);

  return 0;
}


*/



/*

//C语言队列实现广度优先遍历 https://blog.csdn.net/xzongyuan/article/details/21880013
// 多线程 链表队列 https://blog.csdn.net/judwenwen2009/article/details/50390378

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define NUM 10
typedef struct _node
{
   int value;
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
  TNode *t_node;
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
      if(pQueue->head == NULL)
      {//when it's empty
           pQueue->head = pQNode;
	   pQueue->tail = pQNode;
      }
      else
      {
           pQueue->tail->next = pQNode;
	   pQueue->tail = pQNode;
      }
}

QNode* deQueue(Queue *pQueue)
{
	if(pQueue->head == NULL)
	{
	   return NULL;
	}

	QNode *deNode= pQueue->head;
	pQueue->head = pQueue->head->next;
        return deNode;
}

TNode* init_TNode(int value)
{
    TNode  *new_node = (TNode*)malloc(sizeof(TNode));
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


int insert_tree(Tree pTree,int pValue)
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
       return 0;
   }


   if(pValue < pTree->value)
        if(insert_tree(pTree->left,pValue)==0)
        {
	   //no left child any more,set a new left child to pTree
	   pTree->left = tNode;
   	   printf("insert :%d\n",pValue);
	}
   if(pValue > pTree->value)
        if(insert_tree(pTree->right,pValue)==0)
        {
           pTree->right = tNode;
	   printf("insert :%d\n",pValue);
        }
}

Tree creatTree()
{
    srand(time(NULL));
    Tree root = init_TNode(rand()%100);
    printf("root is %d\n",root->value);
    int i ;
    for(i=1;i<NUM;i++)
    {
        insert_tree(root,rand()%100);
    }
    printf("creat tree succuess!Tree heigh is:%d\n",get_tree_height(root));
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

   if(!pRoot)
   {
      return 0;
   }

   enQueue(pQueue,pRoot);
   printf("_______________________\n");
   printf("breath begin,enter root:\n");

   while(ifEmpty(pQueue)!=0)
   {
     QNode  *qNode  = deQueue(pQueue);

     //make suer every enQueue Node is not NULL
     if(qNode->t_node->left!=NULL)
       enQueue(pQueue,qNode->t_node->left);
     if(qNode->t_node->right!=NULL)
       enQueue(pQueue,qNode->t_node->right);

     //print the tree node value
     printf("%d ",qNode->t_node->value);
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

*/


/*
//优先队列

#include<stdlib.h>
#include<stdio.h>

#ifndef _Heap_H
#define _Heap_H

#define MIN 0                                                       //假设插入值均严格大于0
//https://blog.csdn.net/duangyhn/article/details/69670609


struct HeapStruct;
typedef struct HeapStruct *Heap;
typedef int Item;

Heap initial(int size);
int isEmpty(Heap H);
int isFull(Heap H);
void insert(Item it,Heap H);
void deleteItem(int pos,Heap H);
void deleteMin(Heap H);
void destroy(Heap H);

static void decreaseKey(int pos,Item tp,Heap H);
static void increaseKey(int pos,Item tp,Heap H);
static void percolateUp(int pos,Item it,Heap H);
static void percolateDown(int pos,Item it,Heap H);

#endif

struct HeapStruct{
	int size;
	int capacity;
	Item *array;
};


Heap initial(int size){
	if(size < 8){
		printf("size too small");
		exit(1);
	}

	Heap H;
	H=malloc(sizeof(struct HeapStruct));
	if(H==NULL){
		printf("arrange heap fail");
		exit(1);
	}

	H->array=malloc(sizeof(Item)*(size+1));
	if(H->array==NULL){
		printf("arrange array fail");
		free(H);
		exit(1);
	}
	H->size=0;
	H->capacity=size;
	H->array[0]=MIN;
	return H;

}

int isEmpty(Heap H){

	return H->size==0;
}

int isFull(Heap H){
	return H->size==H->capacity;
}

void insert(Item it,Heap H){
	if(!isFull(H)){
		H->size++;
		percolateUp(H->size,it,H);
	}
}

void deleteItem(int pos,Heap H){
	if(!isEmpty(H)){
	  if(pos<1 || pos > H->size)
	    return ;
	  decreaseKey(pos,H->array[pos]-H->array[1]+1,H);
	  deleteMin(H);
	}
}

void deleteMin(Heap H){
	if(!isEmpty(H)){
		percolateDown(1,H->array[H->size--],H);
	}

}

void destroy(Heap H){
	if(H!=NULL){
		free(H->array);
		free(H);
		H=NULL;
	}
}

static void decreaseKey(int pos,Item tp,Heap H){
	if(pos<1|| pos>H->size || tp<=0)
	  return ;
	Item it=H->array[pos]-tp;
	percolateUp(pos,it,H);
}

static void increaseKey(int pos,Item tp,Heap H){
	if(pos<1|| pos>H->size || tp<=0)
	  return ;
	Item it=H->array[pos]+tp;
	percolateUp(pos,it,H);
}

static void percolateUp(int pos,Item it,Heap H){
	int i;
	for(i=pos;it < H->array[i/2];i/=2)
	  H->array[i]=H->array[i/2];
	H->array[i]=it;
}

static void percolateDown(int pos,Item item,Heap H){
	int i,child;
	for(i=pos,child=i*2;i*2<=H->size;i=child){
		if(child<H->size && H->array[child] > H->array[child+1])
		  child++;
		if(item > H->array[child])
		  H->array[i]=H->array[child];
		else break;
	}
	H->array[i]=item;
}

void printHeap(Heap H){
	int i;
	if(!isEmpty(H)){
		for(i=1;i<=H->size;i++)
		  printf("%d\t",H->array[i]);
		printf("\n");
	}
}

int main(){
	Heap H=initial(10);
	if(isEmpty(H))
	  printf("H empty\n");

	insert(4,H);
	insert(42,H);
	insert(14,H);
	insert(456,H);
	insert(74,H);
	insert(714,H);

	printHeap(H);
	deleteMin(H);
	printHeap(H);

	deleteItem(3,H);

	printHeap(H);

	destroy(H);

	return 0;

}

*/


复杂版排括号
/*
#include <string.h>

#define ElementType char

struct StackNode
{
  ElementType data;
  int length;
  struct StackNode  *pNext;
};
typedef struct StackNode *Stack;

Stack CreateStack()
{
    Stack MyStack=(Stack)malloc(sizeof(struct StackNode));
    MyStack->pNext=NULL;
    MyStack->length=0;

    return MyStack;


}

void Push(Stack S, ElementType data)
{
    Stack TmpCell=(Stack)malloc(sizeof(struct StackNode));

    TmpCell->data=data;
    TmpCell->pNext=S->pNext;
    S->pNext=TmpCell;//不停的移送，总是关注最后一块和倒数第二块
}


ElementType Pop(Stack S)
{
    if(S->pNext==NULL)
    {
    printf("empty\n");
    exit(0);
    }

    Stack Temp;
    Temp=S->pNext;
    S->pNext=Temp->pNext;
    ElementType T=Temp->data;
    free(Temp);
    return T;

}
ElementType GetTop(Stack S)
{
    if(!S->pNext)
     {
    printf("empty\n");
    exit(0);
    }

    Stack Temp;
    Temp=S->pNext;
    ElementType T= Temp->data;
    return T;

}


int main()
{
    gElementType T;
    Stack S1=CreateStack();
    char ch[80];
    printf("input parentheses number:\n");
    int n=0;
    scanf("%d",&n);
    printf("input formula\n");
    scanf("%s",ch);
    int i=0;
    char need;
    int flag=0;
    for(i;i<n;i++)
    {
        switch (ch[i])
        {
           case '[':
           {
               need=']';
               Push(S1,need);
               S1->length++;
               break;
           }

           case '{':
           {
               need='}';
               Push(S1,need);
               S1->length++;
               break;
           }
         case '(':
                {
                    need=')';
                    Push(S1,need);
                    S1->length++;
                    break;
                }
        case'<':
             {
                 need='>';
                 Push(S1,need);
                 S1->length++;
                 break;
             }

        case'/':
            {
                need='\\';
                Push(S1,need);
                S1->length++;
                break;
            }


        case']':
        {
            if(GetTop(S1)==']')
            {
                ElementType T=Pop(S1);
                S1->length--;
            }
            else
            {
                flag=1;
            }
            break;
        }


        case '}':
        {
            if(GetTop(S1)=='}')
            {
                ElementType T=Pop(S1);
                S1->length--;
            }
            else
            {

                flag=1;

            }
            break;
        }
        case ')':
        {
            if(GetTop(S1)==')')
            {
                ElementType T=Pop(S1);
                S1->length--;
            }
            else
            {
                flag=1;
            }
            break;

        }

        case'\\':
        {
            if(GetTop(S1)=='\\')
            {
               T=Pop(S1);
               S1->length--;

            }
            else
            {
                flag=1;
            }
            break;
        }


        default:
        {
            flag=1;
            break;
        }


        }




    }

    printf("s1->length=%d flag=%d  \n",S1->length,flag);
      if(S1->length==0&&flag==0)
        {
            puts("successfully inputed");

        }
        else
        {
            puts("failed");
        }








    return 0;
}

*/
