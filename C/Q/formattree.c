#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define NUM 6


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
   Queue *queue=(Queue*)malloc(sizeof(Queue));
   queue->head = queue->tail = NULL;
   return queue;
}


void enQueue(Queue *pQueue,TNode *pTNode,int pDepth)
{

      QNode *pQNode = (QNode *)malloc(sizeof(QNode));
      pQNode->depth = pDepth;
      pQNode->blank = 0; //default config
      if(pTNode==NULL)
      {
         //change default setting; 1 means it's blank QNode
         pQNode->blank =1;
      }

      pQNode->t_node= pTNode;

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

	QNode *deNode;
	deNode = (QNode*)malloc(sizeof(QNode));


		deNode= pQueue->head;

    pQueue->head = pQueue->head->next;
    //pQueue->head = pQueue->head->next;

	//deNode = deNode->next;

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

Tree creatTree(int num)
{
    srand(time(NULL));
    Tree root = init_TNode(rand()%100);
    printf("root is %d\n",root->value);
    int i ;
    for(i=1;i<num;i++)
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
   int height = get_tree_height(pRoot);
   int pad_num = 3;
   //compare to the node's depth in the "while loop"
   int current_depth = 1;
   if(!pRoot)
   {
      return 0;
   }

   enQueue(pQueue,pRoot,1);

   printf("_______________________\n");
   printf("breath begin,enter root:\n");

   while(ifEmpty(pQueue)!=0)
   {

     QNode  *qNode  = deQueue(pQueue);
     //the sub node's depth is 1 more then the parent's
     int child_depth = qNode->depth + 1 ;

	 //之前深度已经赋值1了，enQueue(pQueue,pRoot,1);这时候是输入第一层子树，即第二层,保证最后一行之后不再有新的，因为+1了，提早到达范围边界

     if(qNode->depth > current_depth)
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
//二进制常用变换

     int pad_front = (1<< (height - current_depth))-1;//最后一行=0倒推的式子！ 0=1<<0-1

     if((qNode->blank == 1))
     {
       //add the parent node's padding:2
        if(pad_front == 0)    printf("%*s%*s",pad_num,"o",pad_num," ");//此处pad_num=3，那么例如这个地方就是留了3个位置，两个空格和一个"o"
        //如果第一个数是四位，那么就是前三位+多一位，多一位后面重新开始归零计算，这样会不齐，比如creatTree 里面把rand()%100变成rand()%100000000不齐的会很明显
        //所以最好根据预估的位数，计算设置相应的pad，打印才会整齐
        else                  printf("%*s%*s%*s",pad_front*pad_num," ",pad_num,"o",(1+pad_front)*pad_num," ");
        //pad_front*pad_num+(1+pad_front)*pad_num=(1+2*pad_front)*pad_num=padding between node
       if(child_depth <= height)
       {
         //enter two NULL sub-tree node.
         //every time you enter NULL TNode,there's corresponding blank QNode.
         enQueue(pQueue,NULL,child_depth);
         enQueue(pQueue,NULL,child_depth);
       }
     }
     else
     {
        if(pad_front == 0)   printf("%*d%*s",pad_num,qNode->t_node->value,pad_num," ");
        else                 printf("%*s%*d%*s",pad_front*pad_num," ",pad_num,qNode->t_node->value,(1+pad_front)*pad_num," ");
       if(child_depth <=height)
       {
     enQueue(pQueue,qNode->t_node->left,child_depth);
         enQueue(pQueue,qNode->t_node->right,child_depth);
       }
     }

   } //while end
     printf("\n-----------\nbreath end!\n-----------\n");

   return 1;
}

int main(int argc,char **argv)
{
  Queue *queue=init_queue();
  int i;

  ifEmpty(queue);
  printf("insert node to queue\n");

  int num = NUM; //default

  if(argc == 2)
  {
    num = atoi(argv[1]);
  }

  Tree root = creatTree(num);
  if(!root)
  {
    printf("create Tree failed!\n");
    return 0;
  }

  breath_travel(root,queue);
  return 0;
}


/*

int main()
{



    printf("%*d",10,20);
    puts(" ");
printf("%*c",20,' ');
puts(" ");
printf("%*s%*s",30,"Hello",20," ");
printf("lalalal");
puts(" ");


    return 0;
}




*/

/*

#include<stdlib.h>

#define NUM 6

typedef struct _node
{
    int value;


    struct _node *left;
    struct _node *right;

}TNode, *Tree;

typedef struct _qnode
{
    TNode *t_node;
    int blank;
    int depth;
    struct _qnode *next;
}QNode;

typedef struct _queue
{
    struct _qnode *head;
    struct _qnode *tail;
}Queue;


Queue *init_queue()
{
    Queue *queue;
    if((queue=(Queue*)malloc(sizeof(Queue)))==NULL)
    {
    puts("error to create queue");
    return 0;
    }

    queue->head=queue->tail=NULL;

    return queue;
}

int enqueue(Queue *pQueue,TNode *pTNode,int new_depth)
{
      QNode *pQNode;
      if((pQNode=(QNode*)malloc(sizeof(QNode)))==NULL)
    {
    puts("error to create Qnode");
    return 0;
    }

    pQNode->t_node=pTNode;

    pQNode->blank=0;
    if(pTNode==NULL)
      {

         pQNode->blank =1;
      }

    pQNode->depth=new_depth;

       if(pQueue->head==NULL)
        {
            pQueue->head=pQNode;
            pQueue->tail=pQNode;
        }

        else
        {
            pQueue->tail->next=pQNode;
            pQueue->tail=pQNode;
        }

        return pQueue;
}

QNode *dequeue(Queue *pQueue)
{
     QNode *pQNode;
      if((pQNode=(QNode*)malloc(sizeof(QNode)))==NULL)
    {
    puts("error to create Qnode");
    return 0;
    }

    if(pQueue->head==NULL)
    {
        puts("nothing to denode");
        return 0;
    }

        pQNode=pQueue->head;
        pQueue->head=pQueue->head->next;

        return pQNode;

}


TNode *init_tnode(int TValue)
{
    TNode *pTNode;
    if((pTNode=(TNode*)malloc(sizeof(TNode)))==NULL)
    {
    puts("error to create TNode");
    return 0;
    }

    pTNode->value=TValue;
    pTNode->left=pTNode->right=NULL;

    return pTNode;

}


int insert_tree(TNode *oTNode,int new_value)
{
      if(!oTNode)
    {
        return 0;
    }



       TNode *pTNode;

    pTNode=init_tnode(new_value);




    if(oTNode->value > new_value)
    {
        if(insert_tree(oTNode->left,new_value)==0)
        {
           oTNode->left=pTNode;
           printf("insert %d\n",new_value);

        }
    }

        if(oTNode->value<new_value)
    {
        if(insert_tree(oTNode->right,new_value)==0)
        {
           oTNode->right=pTNode;
           printf("insert %d\n",new_value);

        }
    }


//return oTNode;

}

TNode *creattree(int num)
{
    srand(time(NULL));


       TNode *pRoot;
       pRoot=init_tnode(rand()%100);

       puts("now create the tree!");
       int i;
        printf("root is %d\n",pRoot->value);
       for(i=1;i<num;i++)
       {
        insert_tree(pRoot,rand()%100);

       }

       printf("finish creating! the height is %d\n\n",tree_height(pRoot));

        return pRoot;
}

int tree_height(TNode *pTNode)
{
    if(!pTNode)
    {
        return 0;
    }

    int lh=0,rh=0;
    lh=tree_height(pTNode->left);
    rh=tree_height(pTNode->right);


    return (lh<rh)?(rh+1):(lh+1);


}

int ifEmpty(Queue *pQueue)
{
    if(pQueue->head==NULL)
    {
        return 0;
    }


    return 1;
}

int breath_travel(Queue *pQueue,TNode *pRoot)
{
        int current_depth=1,pad_num=3;
        QNode *denode;
        int height=tree_height(pRoot);

        int child_depth;
        enqueue(pQueue,pRoot,1);

        while(ifEmpty(pQueue)!=0)
        {
            denode=dequeue(pQueue);
            child_depth=denode->depth +1; //父子结点分别考虑，

            if(current_depth<denode->depth)//父节点
            {
                current_depth=denode->depth;
                 printf("\n\n");
                }
            int pad_front=(1<<(height-current_depth))-1;

            if(denode->blank==1)
            {
                if(pad_front==0) printf("%*s%*s",pad_num,"0",pad_num," ");
                else             printf("%*s%*s%*s",pad_num*pad_front," ",pad_num,"0",pad_num*(pad_front+1)," ");
                if(child_depth<=height)
                {
                    enqueue(pQueue,NULL,child_depth);//返回的是qnode所以没有pqueue->head==0
                    enqueue(pQueue,NULL,child_depth);

                }

            }
            else
            {
                if(pad_front==0)printf("%*d%*s",pad_num,denode->t_node->value,pad_num," ");
                else printf("%*s%*d%*s",pad_num*pad_front," ",pad_num,denode->t_node->value,pad_num*(pad_front+1)," ");
              if(child_depth<=height)
              {
                  enqueue(pQueue,denode->t_node->left,child_depth);
                  enqueue(pQueue,denode->t_node->right,child_depth);


              }

            }


        }




   printf("\n-----------\nbreath end!\n-----------\n");

   return 1;




}


int main(int argc,char **argv)
{
    Queue *queue=init_queue();
   // ifEmpty(queue);
    int num=NUM;
    if(argc==2)
    {
        num=atoi(argv[1]);

    }

    TNode *root=creattree(num);

    breath_travel(queue,root);



    return 0;
}

*/
