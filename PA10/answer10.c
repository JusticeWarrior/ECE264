#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "answer10.h"

/* This tree will be organized by state -> city -> address -> decending review stars and will hold business.tsv pointers and reviews.tsv pointers. */
typedef struct m_BusinessPointerTree
{
	struct m_BusinessPointerTree * left;
	struct m_BusinessPointerTree * right;

	long int businessPointer;
	long int reviewPointer;
} BusinessPointerTree;

static BusinessPointerTree * CreateBusinessTree(long int businessPointer, long int reviewPointer)
{
	BusinessPointerTree * tree = malloc(sizeof(BusinessPointerTree));

	tree->left = NULL;
	tree->right = NULL;

	tree->businessPointer = businessPointer;
	tree->reviewPointer = reviewPointer;

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

/* Sorts data according to State -> City -> Address -> Decending Review Stars. Assumes that files have already been opened.*/
static int businessComp(long int nodeData, long int rootData, long int nodeRev, long int rootRev, FILE * busFp, FILE * revFp)
{
	const char s[2] = "\t";

	char * nodeAddress;
	char * nodeCity;
	char * nodeState;

	fseek(busFp, nodeData, SEEK_SET);
	char line[500];
	fgets(line, 500, busFp);

	strtok(line, s);
	strtok(NULL, s);

	nodeAddress = strtok(NULL, s);
	nodeCity = strtok(NULL, s);
	nodeState = strtok(NULL, s);

	char * rootAddress;
	char * rootCity;
	char * rootState;

	fseek(busFp, rootData, SEEK_SET);

	fgets(line, 500, busFp);

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
			int addressCmp = stricmp(nodeAddress, rootAddress);
			if (addressCmp == 0)
			{
				fseek(revFp, nodeRev, SEEK_SET);
				char * nodeRev;
				strtok(line, s);
				nodeRev = strtok(NULL, s);

				fseek(revFp, rootRev, SEEK_SET);
				char * rootRev;
				strtok(line, s);
				rootRev = strtok(NULL, s);

				return atoi(nodeRev) - atoi(rootRev);
			}
			return addressCmp;
		}
		return cityCmp;
	}

	return stateCmp;
}

static BusinessPointerTree * BusinessTreeInsert(BusinessPointerTree * node, BusinessPointerTree * root,
	int(*compFunc)(long int nodeData, long int rootData, long int nodeRev, long int rootRev, FILE * busFp, FILE * revFp), FILE * busFp, FILE * revFp)
{
	if (root == NULL)
		return node;
	int comp = compFunc(node->businessPointer, root->businessPointer, node->reviewPointer, root->reviewPointer, busFp, revFp);
	if (comp < 0)
		root->left = BusinessTreeInsert(node, root->left, compFunc, busFp, revFp);
	else if (comp > 0)
		root->right = BusinessTreeInsert(node, root->right, compFunc, busFp, revFp);
	else
		return root; // Throw out duplicates (although there shouldn't be any)

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

static YelpDataTree * CreateYelpDataTree(char * name, long int businessPointer, long int reviewPointer)
{
	YelpDataTree * tree = malloc(sizeof(YelpDataTree));

	tree->left = NULL;
	tree->right = NULL;

	tree->locations = CreateBusinessTree(businessPointer, reviewPointer);
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

static YelpDataTree * YelpDataInsert(YelpDataTree * node, YelpDataTree * root, FILE * busFp, FILE * revFp)
{
	if (root == NULL)
		return node;

	// Sort names according to non case sensitive data
	int comp = stricmp(node->name, root->name);
	if (comp < 0)
		root->left = YelpDataInsert(node, root->left, busFp, revFp);
	else if (comp > 0)
		root->right = YelpDataInsert(node, root->right, busFp, revFp);
	else
	{
		BusinessTreeInsert(node->locations, root->locations, businessComp, busFp, revFp);
		DestroyYelpNode(node);
	}
		

	return root;
}

struct YelpDataBST* create_business_bst(const char* businesses_path,
	const char* reviews_path)
{
	const char s[2] = "\t";

	FILE * busFp = fopen(businesses_path, "r");
	FILE * revFp = fopen(reviews_path, "r");

	char busLine[200];
	char * busId;
	char * name;
	char revLine[200];
	char * revId;
	
	fgets(busLine, 200, busFp);
	busId = strtok(busLine, s);
	name = strtok(NULL, s);

	fgets(revLine, 200, revFp);
	revId = strtok(revLine, s);

	YelpDataTree * root = CreateYelpDataTree(name, 0, 0);

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