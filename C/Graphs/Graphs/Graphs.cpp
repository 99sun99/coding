#include"Graphs.h"

void Clear(int* visit)
{
	for(int i=0;i<n;i++)
	{
		visit[i]=0;
	}
}

int main()
{
	int i,j;
	edgenode* p;
	graph *grp=(graph *)malloc(sizeof(graph));
	vexnode *ga=(vexnode *)malloc(sizeof(vexnode)*n);
	int visit[n]={0};
	CreatGraph(grp);
	CreatAdjList(ga,grp);

	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("%3d ",grp->arcs[i][j]);
		}
		printf("\n");
	}

	for(i=0;i<n;i++)
	{

		p=ga[i].link;
		printf("%d %3c ",i,ga[i].vex);
		while(p!=NULL)
		{
			printf("%3d ",p->adjvex);
			p=p->next;
		}
		printf("\n");
	}

	dfsMatrix(grp,0,visit);
	Clear(visit);
	dfsList(ga,0,visit);
	Clear(visit);
	bfsMatrix(grp,visit,0);
	Clear(visit);
	bfsList(ga,visit,0);
	return 0;
}

