#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "answer09.h"

BusinessNode * create_node(char * stars, char * name, char * address)
{
	BusinessNode * node = malloc(sizeof(BusinessNode));
	node->stars = strdup(stars);
	node->name = strdup(name);
	node->address = strdup(address);

	return NULL;
}

BusinessNode * tree_insert(BusinessNode * node, BusinessNode * root)
{
	if (root == NULL)
	{
		root = node;
		return root;
	}

	int comp = strcmp(node->name, root->name);
	if (comp == 0)
		return root;
	else if (comp < 0)
		tree_insert(node, root->left);
	else
		tree_insert(node, root->right);
	
	return root;
}

BusinessNode * load_tree_from_file(char * filename)
{
	return NULL;
}

BusinessNode * tree_search_name(char * name, BusinessNode * root)
{
	if (root == NULL)
		return NULL; // BASE CASE

	int comp = strcmp(name, root->name);
	if (comp == 0)
		return root; // WE FOUND THE NAME!
	else if (comp < 0)
		root = tree_search_name(name, root->left);
	else
		root = tree_search_name(name, root->right);

	return root;
}

void print_node(BusinessNode * node)
{
	fprintf(stdout, "%s\t%s\t%s\n", node->stars, node->name, node->address);
}

void print_tree(BusinessNode * tree)
{
	if (tree == NULL)
		return;

	print_tree(tree->left);
	print_node(tree);
	print_tree(tree->right);
}

void destroy_tree(BusinessNode * root)
{
	if (root == NULL)
		return;

	destroy_tree(root->left);
	destroy_tree(root->right);

	free(root->stars);
	free(root->name);
	free(root->address);
	free(root);
}