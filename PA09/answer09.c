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
	return NULL;
}

BusinessNode * load_tree_from_file(char * filename)
{
	return NULL;
}

BusinessNode * tree_search_name(char * name, BusinessNode * root)
{
	return NULL;
}

void print_node(BusinessNode * node)
{
}

void print_tree(BusinessNode * tree)
{

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