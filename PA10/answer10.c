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

/* Sorts data according to State -> City -> Address. Assumes that a file has already been opened.*/
static int businessComp(long int nodeData, long int rootData, FILE * fp)
{
	const char s[2] = "\t";

	char * nodeAddress;
	char * nodeCity;
	char * nodeState;

	fseek(fp, nodeData, SEEK_SET);
	char line[500];
	fgets(line, 500, fp);

	strtok(line, s);
	strtok(NULL, s);

	nodeAddress = strtok(NULL, s);
	nodeCity = strtok(NULL, s);
	nodeState = strtok(NULL, s);

	char * rootAddress;
	char * rootCity;
	char * rootState;

	fseek(fp, rootData, SEEK_SET);

	fgets(line, 500, fp);

	strtok(line, s);
	strtok(NULL, s);

	rootAddress = strtok(NULL, s);
	rootCity = strtok(NULL, s);
	rootState = strtok(NULL, s);

	int stateCmp = stricmp(nodeState, rootState);
	if (stateCmp == 0)
	{
		int cityCmp = stricmp(nodeCity, rootCity);
		if (cityCmp == 0)
		{
			return stricmp(nodeAddress, rootAddress);
		}
		return cityCmp;
	}

	return stateCmp;
}

static BusinessPointerTree * BusinessTreeInsert(BusinessPointerTree * node, BusinessPointerTree * root,
	int (*compFunc)(long int nodeData, long int rootData, FILE * fp), FILE * fp)
{
	if (root == NULL)
		return node;
	int comp = compFunc(node->businessPointer, root->businessPointer, fp);
	if (comp < 0)
		root->left = BusinessTreeInsert(node, root->left, compFunc, fp);
	else if (comp > 0)
		root->right = BusinessTreeInsert(node, root->right, compFunc, fp);
	else
	{
		// DEAL WITH REVIEWS OF THE SAME LOCATION!
	}

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

/* Destroys a single YelpDataTree node without destroying the locations tree or the right and left nodes. */
static void DestroyYelpNode(YelpDataTree * node)
{
	if (node == NULL)
		return;

	free(node);
}

static YelpDataTree * YelpDataInsert(YelpDataTree * node, YelpDataTree * root, FILE * fp)
{
	if (root == NULL)
		return node;

	// Sort names according to non case sensitive data
	int comp = stricmp(node->name, root->name);
	if (comp < 0)
		root->left = YelpDataInsert(node, root->left, fp);
	else if (comp > 0)
		root->right = YelpDataInsert(node, root->right, fp);
	else
	{
		BusinessTreeInsert(node->locations, root->locations, businessComp, fp);
		DestroyYelpNode(node);
	}
		

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