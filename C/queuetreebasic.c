//改之前 https://blog.csdn.net/xzongyuan/article/details/21830097

#include<stdio.h>
#include<stdlib.h>

typedef struct _node
{
   long long value;//块太小识别不出来？
   struct _node *next;
}Node;

typedef struct _Queue
{
   Node *head;
   Node *tail;
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

	//free(deNode);

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


    ifEmpty(queue);

  return 0;
}
