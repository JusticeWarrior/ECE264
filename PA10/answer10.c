#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "answer10.h"

/* This tree will be organized by state -> city -> address and will hold business.tsv pointers and reviews.tsv pointers. */
typedef struct m_BusinessPointerTree
{
	struct m_BusinessPointerTree * left;
	struct m_BusinessPointerTree * right;

	long int businessPointer;
	long int reviewPointer;
	int numReviews;
} BusinessPointerTree;

static BusinessPointerTree * CreateBusinessTree(long int businessPointer, long int reviewPointer, int numReviews)
{
	BusinessPointerTree * tree = malloc(sizeof(BusinessPointerTree));

	tree->left = NULL;
	tree->right = NULL;

	tree->businessPointer = businessPointer;
	tree->reviewPointer = reviewPointer;
	tree->numReviews = numReviews;

	return tree;
}

static void DeconstructBusinessTree(BusinessPointerTree * tree)
{
	if (tree == NULL)
		return;
	DeconstructBusinessTree(tree->left);
	DeconstructBusinessTree(tree->right);

	free(tree);
}

BusinessPointerTree * BusinessTreeInsert(BusinessPointerTree * node, BusinessPointerTree * root,
	int (*compFunc)(long int nodeData, long int rootData))
{
	if (root == NULL)
		return node;

	int comp = compFunc(node->businessPointer, root->businessPointer);
	if (comp <= 0)
		root->left = BusinessTreeInsert(node, root->left, compFunc);
	else //// NEED TO DESTROY DUPLICATE NAME NODE!!!!
		sdfdsroot->right = BusinessTreeInsert(node, root->right, compFunc);

	return root;
}

/* This tree will be built during the create_business_bst() function. */
typedef struct YelpDataBST
{
	struct YelpDataBST * left;
	struct YelpDataBST * right;

	BusinessPointerTree * locations;
	char * name;
} YelpDataTree;

static YelpDataTree * CreateYelpDataTree(char * name, long int businessPointer, long int reviewPointer, int numReviews)
{
	YelpDataTree * tree = malloc(sizeof(YelpDataTree));

	tree->left = NULL;
	tree->right = NULL;

	tree->locations = CreateBusinessTree(businessPointer, reviewPointer, numReviews);
	tree->name = strdup(name);

	return tree;
}

void destroy_business_bst(struct YelpDataBST* bst)
{
	if (bst == NULL)
		return;

	destroy_business_bst(bst->left);
	destroy_business_bst(bst->right);

	DeconstructBusinessTree(bst->locations);
	free(bst->name);
	free(bst);
}


YelpDataTree * YelpDataInsert(YelpDataTree * node, YelpDataTree * root)
{
	if (root == NULL)
		return node;

	int comp = strcmp(node->name, root->name);
	if (comp < 0)
		root->left = YelpDataInsert(node, root->left);
	else if (comp > 0)
		root->right = YelpDataInsert(node, root->right);
	else
		BusinessTreeInsert(node->locations, root->locations, strcmp);

	return root;
}

struct YelpDataBST* create_business_bst(const char* businesses_path,
	const char* reviews_path)
{
	return NULL;
}

struct Business* get_business_reviews(struct YelpDataBST* bst,
	char* name, char* state, char* zip_code)
{
	return NULL;
}



void destroy_business_result(struct Business* b)
{

}