#include"stdlib.h"
#include"stddef.h"
#include"stdio.h"
#define n 6
#define e 8

typedef struct graph
{
	char vexs[n];
	int arcs[n][n];
}graph;

typedef struct node
{
	int adjvex;
	struct node *next;
}edgenode;

typedef struct vexnode
{
	char vex;
	edgenode *link;
}vexnode;



void CreatGraph(graph *ga)
{
	int i,j,k;
	printf("please input vex\n");
	for(i=0;i<n;i++)
	{
		scanf("%c",&(ga->vexs[i]));
		getchar();
		printf(" *ok* \n");
	}
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			ga->arcs[i][j]=0;
		}
	}
	printf("input edge\n");
	for(k=0;k<e;k++)
	{
		scanf("%d,%d",&i,&j);
		getchar();
		printf("\n");
		ga->arcs[i][j]=1;
		ga->arcs[j][i]=1;
	}
}

void CreatAdjList(vexnode *ga,graph *grp)
{
	int i,j;//µü´ú²ÎÊý
	edgenode *s;
	for(i=0;i<n;i++)
	{
		ga[i].vex=grp->vexs[i];
		ga[i].link=NULL;
	}
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if(grp->arcs[i][j]!=0)
			{
				s=(edgenode* )malloc(sizeof(edgenode));
				s->adjvex=j;
				s->next=ga[i].link;
				ga[i].link=s;
			}
		}
	}
}

void dfsMatrix(graph* grp,int i,int* visit)
{
	int j;
	printf("%3c  ",grp->vexs[i]);
	visit[i]=1;
	for(j=0;j<n;j++)
	{
		if((grp->arcs[i][j]==1)&& (!visit[j]))
		{
			dfsMatrix(grp,j,visit);
		}
	}
}

void dfsList(vexnode *ga,int i,int* visit)
{
	edgenode *p;
	printf("%3c  ",ga[i].vex);
	visit[i]=1;
	p=ga[i].link;
	while(p!=NULL)
	{
		if(!visit[p->adjvex])
		{
			dfsList(ga,p->adjvex,visit);
		}
		p=p->next;
	}
}

typedef struct 
{
	int data[n];
	int rear,front;
}queue;

void ClearQueue(queue *q)
{
	q->rear=q->front=-1;
}

bool isEmpty(queue *q)
{
	if(q->rear==q->front)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Enqueue(queue* q,int x)
{
	if(q->rear<n-1)
	{
		q->rear++;
		q->data[q->rear]=x;
	}
	else
		printf("error\n");
}

int Dequeue(queue* q)
{
	if(!isEmpty(q))
	{
		q->front++;
		return q->data[q->front];
	}
	else return NULL;
}

void bfsMatrix(graph* grp,int* visit,int k)
{
	int i,j;
	queue *q=(queue *)malloc(sizeof(queue));
	ClearQueue(q);
	printf("%3c  ",grp->vexs[k]);
	visit[k]=1;
	Enqueue(q,k);
	while(!isEmpty(q))
	{
		i=Dequeue(q);
		for(j=0;j<n;j++)
		{
			if((grp->arcs[i][j]==1) && (!visit[j]))
			{
				visit[j]=1;
				printf("%3c  ",grp->vexs[j]);
				Enqueue(q,j);
			}
		}
	}
}

void bfsList(vexnode *ga,int* visit,int k)
{
	int i,j;
	edgenode *p;
	queue *q=(queue *)malloc(sizeof(queue));
	ClearQueue(q);
	printf("%3c  ",ga[k].vex);
	visit[k]=1;
	Enqueue(q,k);
	while(!(isEmpty(q)))
	{	
		i=Dequeue(q);
		p=ga[i].link;
		do
		{
			if(!visit[p->adjvex])
			{
				printf("%3c  ",ga[p->adjvex].vex);
				Enqueue(q,p->adjvex);
				visit[p->adjvex]=1;				
			}
			p=p->next;
		}while(p!=NULL);
	}

}

