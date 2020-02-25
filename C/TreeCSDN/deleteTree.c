#include "C:\work\coding\C\TreeCSDN\tree.c"
#include<stdio.h>
#include<stdlib.h>


TNode* delete_tree_node(TNode *r, TNode *delete_node)
{
	TNode *parent,*min,*max,*tmp,*tmproot;
	
	if (delete_node == NULL||r==NULL)
	{
		puts("nothing to delelte");
		tmp = NULL;
		return tmp;
	}


	if (delete_node == r)
	{
		if(r->right==NULL)
		{
			tmp = r;
			r = r->left;
			tmp->left = NULL;
			free(tmp);
			return r;
		}
		else if (r->left == NULL)
		{
			tmp = r;
			r = r->right;
			tmp->right = NULL;
			free(tmp);
			return r;
		}
		
		else 
		{
			tmp = r;
			tmproot = getMinNodeBinSearchTree(r->right);
			if (tmproot == tmp->right)
			{
				tmproot->left= tmp->left;
			}else{
				parent = getParentBinSearchTree(r, tmproot);
				tmproot->left=tmp->left;
				tmproot->right=tmp->right ;
				parent->left = NULL;
				free(tmp);	
			}
			r = tmproot;
			return r;
		}
		

		

	}



	parent = getParentBinSearchTree(r, delete_node);

	if (parent == NULL)
	{
		puts("nothing to delelte");
		r = NULL;
		return r;
	}
	


	if(delete_node->left==NULL && delete_node->right == NULL)
	{ 
		if (parent->left == delete_node)
		{
			//tmp = parent->left;
			parent->left = NULL;
			free(delete_node);
		}
		if (parent->right == delete_node)
		{
			parent->right = NULL;
			free(delete_node);
		}
	}
	else if (delete_node->left != NULL && delete_node->right == NULL)
	{
		if (parent->left == delete_node)
		{
			//tmp = parent->left;
			parent->left = delete_node->left;
			free(delete_node);
		}
		if (parent->right == delete_node)
		{
			parent->right = delete_node->left;
			free(delete_node);
		}

		
		
	}
	else if (delete_node->left == NULL && delete_node->right != NULL)
	{
		if (parent->left == delete_node)
		{
			//tmp = parent->left;
			parent->left = delete_node->right;
			free(delete_node);
		}
		if (parent->right == delete_node)
		{
			parent->right = delete_node->right;
			free(delete_node);
		}

	}
	else
	{ 
	

		
			min = getMinNodeBinSearchTree(delete_node->right);
			tmp = getParentBinSearchTree(r,min);
			if (tmp->left == min)
			{
				tmp->left = NULL;
			}
			if (tmp->right == min)
			{
				tmp->right = NULL;
			}
			if (parent->right == delete_node)
			{
				parent->right = min;
				min->left = delete_node->left;

				if(min->right==NULL)
				min->right = delete_node->right;

				free(delete_node);
			}
			else if (parent->left == delete_node)
			{
				parent->left = min;
				min->left = delete_node->left;

				if (min->right == NULL)
					min->right = delete_node->right;

				free(delete_node);

			}


	}
	return r;
}





int main(int argv,char *argc )
{
	Queue *queue = init_queue();
	ifEmpty(queue);
	
	int num = 8;
	if (argv == 2)
	{
		num = atoi(argc[1]);
	}

	TNode *r = creatTree(num);
	breath_travel(r, queue);
	int delete_number;

	while(r)
	{ 
		puts("enter the number to be deleted\n");
		scanf_s("%d", &delete_number);
		TNode* delete_node = searchBinSearchTree(r, delete_number);;
		r = delete_tree_node(r, delete_node);
		puts("now delete it");
		free(queue);
		queue = init_queue();
		breath_travel(r, queue);
	}
	
	free(queue);
	free(r);
	puts("Nothing to delete");

	return 0;
}


