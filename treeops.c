#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "treeops.h"

tree_t *make_empty_tree(int func(void*,void*))
{
	tree_t *tree;
	tree = malloc(sizeof(*tree));
	assert(tree!=NULL);
	
	tree->root = NULL;
	
	tree->cmp = func;
	return tree;
	
}

int is_empty_tree(tree_t *tree)
{
	assert(tree!=NULL);
	return tree->root == NULL;
}

static void *recursive_search_tree(node_t *root,void *key, int cmp(void*,void*))
{
	int outcome;
	if(!root)
	{
		return NULL;	
	}
	if((outcome = cmp(key,root->data))<0)
	{
		return recursive_search_tree(root->left,key,cmp);
	}
	else if (outcome > 0)
	{
		return recursive_search_tree(root->right,key,cmp);
	}
	else
	{
		return root->data;		
	}

}

void *search_tree(tree_t *tree,void *key)
{
	assert(tree!=NULL);
	return recursive_search_tree(tree->root,key,tree->cmp);
}

static node_t *recursive_insert(node_t *root, node_t *new,int cmp(void*,void*))
{
	if (root==NULL)
	{
		return new;	
	}
	else if((cmp(new->data,root->data))<0)
	{
		root->left=recursive_insert(root->left,new,cmp);	
	}
	else
	{
		root->right=recursive_insert(root->right,new,cmp);	
	}
	return root;
}

tree_t *insert_in_order(tree_t *tree,void *value)
{
	node_t *new;
	new=malloc(sizeof(*new));
	assert(tree!=NULL && new!=NULL);
	new->data = value;
	new->left = new->right=NULL;
	tree->root=recursive_insert(tree->root,new,tree->cmp);
	return tree;
}

static void recursive_traverse(node_t *root,void action(void*))
{
	if(root)
	{
		recursive_traverse(root->left,action);
		action(root->data);
		recursive_traverse(root->right,action);
	}
}

void traverse_tree(tree_t *tree,void action(void*))
{
	assert(tree!=NULL);
	recursive_traverse(tree->root,action);
}

static void recursive_free_tree(node_t *root)
{
	if(root)
	{
		recursive_free_tree(root->left);
		recursive_free_tree(root->right);
		free(root);
	}
}

void free_tree(tree_t *tree)
{
	assert(tree!=NULL);
	recursive_free_tree(tree->root);
	free(tree);
}