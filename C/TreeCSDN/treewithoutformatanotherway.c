#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define NUM 10
// change denote part and breath travel part

typedef struct _node
{
    int value;

    struct _node *left;
    struct _node *right;
}TNode,*Tree;

typedef struct _q_node
{
    TNode *t_node;
    long long length;

    struct _q_node *next;

}QNode;

typedef struct _queue
{
    QNode *head;
    QNode *tail;
}Queue;


TNode *init_TNode(int i)
{
    TNode *new_node;
    if((new_node=(TNode*)malloc(sizeof(TNode)))==NULL)
    {
        puts("error to start a new node");
        return NULL;
    }

    new_node->value=i;
    new_node->left=new_node->right=NULL;
    return new_node;

}

Queue *init_Queue()
{
    Queue *queue;
    if((queue=(Queue*)malloc(sizeof(Queue)))==NULL)
    {
        puts("error to start a new Queue");
        return NULL;
    }

    queue->head=queue->tail=NULL;

    return queue;
}

int enQueue(Queue *pQueue,TNode *pTNode)//
{
    QNode *pQNode;
     if((pQNode=(QNode*)malloc(sizeof(QNode)))==NULL)
    {
        puts("error to start a new tmp node");
        return 0;
    }

    pQNode->t_node=pTNode;



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

//return pQueue;

}

TNode *deQueue(Queue *pQueue)
{
    if((pQueue->head)==NULL)
    {
        puts("empty queue");
        return NULL;
    }

    TNode *denode;//?
    if((denode=(QNode*)malloc(sizeof(QNode)))==NULL)

 {
        puts("error to start a new de_node");
        return NULL;
    }


        denode=pQueue->head->t_node;
        pQueue->head=pQueue->head->next;

        return denode;
}

int insert_tree(Tree pRoot,int i )// what if return value is a pointer?
{
        TNode *pTNode=init_TNode(i);

        if(!pRoot)
        {
            return 0;
        }

        if(i< pRoot->value)
        {
            if((insert_tree(pRoot->left,i))==0)
            {
                pRoot->left=pTNode;
                printf("insert value %d\n",i);//?
            }

        }
           if(i>pRoot->value)
        {
            if((insert_tree(pRoot->right,i))==0)
            {
                pRoot->right=pTNode;
                printf("insert value %d\n",i);//?
            }

        }


}



TNode *creat_tree()
{
    srand(time(NULL));

    TNode *pRoot=init_TNode(rand()%100);
    printf("the root is %d\n",pRoot->value );
    int i;
    for(i=1;i<NUM;i++)
    {
        insert_tree(pRoot,rand()%100);

    }

    printf("the height is %d\n",tree_height(pRoot) );

    return pRoot;

}

int tree_height(TNode *pRoot)
{
    if(!pRoot)
    {
        return 0;
    }

    int lh=0,rh=0;
    lh=tree_height(pRoot->left);
    rh=tree_height(pRoot->right);

return (lh<rh)?(rh+1):(lh+1);
}

int ifEmpty(Queue *pQueue)
{
    if((pQueue->head)==NULL)
    {
    //puts("empty tree");
        return 0;
    }

    return 1;

}


int  breath_travel(Queue *pQueue,TNode *pRoot)//?
{
   if(pRoot==NULL)
   {
      return 0;
   }
   int count = 0;

    enQueue(pQueue,pRoot);

    puts("now begin to travel");
   // int i=0;
	while (count < NUM)
	{
		count++;

       TNode *denode=deQueue(pQueue);
        //printf("[%d]",i++);

        if(denode->left!=NULL)
        {
            enQueue(pQueue,denode->left);
        }


        if(denode->right!=NULL)
        {
            enQueue(pQueue,denode->right);
        }



        printf(" %d  ",denode->value);//

    }


puts(" ");

puts("=============================================");

puts("====================end of travel ===============");

return 1;
}










int main()
{

    Queue *queue=init_Queue();

    TNode *root=creat_tree();

    breath_travel(queue,root);

    return 0;
}

/*
//revise without qnode
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define NUM 10



typedef struct _node
{
    int value;

    struct _node *left;
    struct _node *right;
    struct _node *next;


}TNode, *Tree;


typedef struct _queue
{
    struct _node *head;
    struct _node  *tail;


}Queue;


TNode *init_TNode(int i)
{
    TNode *new_node;

    if((new_node=(Tree)malloc(sizeof(TNode)))==NULL)
   {
    puts("error to create new node");
    return 0;
    }

    new_node->value=i;

    new_node->left=new_node->right=new_node->next=NULL;
    return new_node;

}


Queue *init_Queue()
{

    Queue *pQueue;

     if((pQueue=(Queue*)malloc(sizeof(Queue)))==NULL)
   {
    puts("error to create new node");
    return 0;
    }

    pQueue->head=pQueue->tail=NULL;
    return pQueue;


}


Queue  *enqueue(Queue *pQueue,Tree pNode)
{
    if(pQueue->head==NULL)
    {
        pQueue->head=pNode;
        pQueue->tail=pNode;


    }

    else
    {
        pQueue->tail->next=pNode;
        pQueue->tail=pNode;
    }

        return pQueue;

}

TNode *dequeue(Tree pRoot,Queue *pQueue)
{
    TNode *de_node;
    if((de_node=(TNode *)malloc(sizeof(TNode)))==NULL)
    {
        puts("error to create de node");
    return 0;
    }

    de_node=pQueue->head;
    pQueue->head=pQueue->head->next;
    return de_node;


}

int insert_tree(Tree pTNode, int i)
{  TNode *new_node;


    new_node=init_TNode(i);


    if(!pTNode)
    {
        return 0;
    }


    if(i<pTNode->value)
{
    if((insert_tree(pTNode->left,i))==0)
    {
        pTNode->left=new_node;
        printf("insert %d\n",i);

    }

}

if(i>pTNode->value)
{
    if((insert_tree(pTNode->right,i))==0)
    {
        pTNode->right=new_node;
        printf("insert %d\n",i);

    }

}



}


TNode *creattree()
{
        srand(time(NULL));

        TNode *pRoot=init_TNode(rand()%100);
        printf("root is %d\n",pRoot->value);

        int i;
        for(i=0;i<NUM;i++)
        {
            insert_tree(pRoot,rand()%100);
        }

        printf("the height is %d\n",tree_height(pRoot));


        return pRoot;


}


int tree_height(TNode *pRoot)
{
   if(!pRoot)
   {
       return 0;
   }

    int lh=0,rh=0;
    lh=tree_height(pRoot->left);
    rh=tree_height(pRoot->right);

    return (lh<rh)?(rh+1):(lh+1);

}

int ifEmpty(Queue *pQueue)
{
    if(pQueue->head==NULL)
    {
        return 0;


    }

    else
    {
        return 1;
    }
}



int travel_breath(Queue *pQueue, TNode *pTNode)
{

    enqueue(pQueue,pTNode);

    while(ifEmpty(pQueue)!=0)
    {
        TNode *denode=dequeue(pTNode,pQueue);

        if(denode->left!=0)
        {
            enqueue(pQueue,denode->left);
        }
        if(denode->right!=0)
        {
            enqueue(pQueue,denode->right);
        }

        printf(" %d  ",denode->value);

    }


}


int main()
{
    Queue *root=init_Queue();

    TNode  *tree_node=creattree();

    travel_breath(root,tree_node);




    return 0;
}






*/









