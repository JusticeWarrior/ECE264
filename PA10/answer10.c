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
	char nodeLine[6000];
	fgets(nodeLine, 259, busFp);

	strtok(nodeLine, s);
	strtok(NULL, s);

	nodeAddress = strtok(NULL, s);
	nodeCity = strtok(NULL, s);
	nodeState = strtok(NULL, s);

	char * rootAddress;
	char * rootCity;
	char * rootState;

	char rootLine[6000];
	fseek(busFp, rootData, SEEK_SET);

	fgets(rootLine, 259, busFp);

	strtok(rootLine, s);
	strtok(NULL, s);

	rootAddress = strtok(NULL, s);
	rootCity = strtok(NULL, s);
	rootState = strtok(NULL, s);

	int stateCmp = stricmp(rootState, nodeState);
	if (!stateCmp)
	{
		int cityCmp = stricmp(rootCity, nodeCity);
		if (!cityCmp)
		{
			int addressCmp = stricmp(rootAddress, nodeAddress);
			if (!addressCmp)
			{
				fseek(revFp, nodeRev, SEEK_SET);
				fgets(nodeLine, 6000, revFp);
				char * nodeStars;
				char * nodeText;
				strtok(nodeLine, s);
				nodeStars = strtok(NULL, s);
				strtok(NULL, s);
				strtok(NULL, s);
				strtok(NULL, s);
				nodeText = strtok(NULL, s);

				fseek(revFp, rootRev, SEEK_SET);
				fgets(rootLine, 6000, revFp);
				char * rootStars;
				char * rootText;
				strtok(rootLine, s);
				rootStars = strtok(NULL, s);
				strtok(NULL, s);
				strtok(NULL, s);
				strtok(NULL, s);
				rootText = strtok(NULL, s);

				int starsCmp = atoi(nodeStars) - atoi(rootStars);
				if (!starsCmp)
				{
					return stricmp(rootText, nodeText);
				}
				return starsCmp;
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
	else if (comp >= 0)
		root->right = BusinessTreeInsert(node, root->right, compFunc, busFp, revFp);

	return root;
}

/* This tree will be built during the create_business_bst() function. */
typedef struct YelpDataBST
{
	struct YelpDataBST * left;
	struct YelpDataBST * right;

	BusinessPointerTree * locations;
	char * name;
	char * businessPath;
	char * reviewPath;
} YelpDataTree;

static YelpDataTree * CreateYelpDataTree(char * name, long int businessPointer, long int reviewPointer,
	const char * businessPath, const char * reviewPath)
{
	YelpDataTree * tree = malloc(sizeof(YelpDataTree));

	tree->left = NULL;
	tree->right = NULL;

	if (businessPath != NULL)
	{
		tree->businessPath = strdup(businessPath);
		tree->reviewPath = strdup(reviewPath);
	}
	
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
	free(bst->businessPath);
	free(bst->reviewPath);
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

	FILE * busFp = fopen(businesses_path, "rb");
	FILE * revFp = fopen(reviews_path, "rb");

	char busLine[259];
	char * busId;
	char * name;
	char revLine[6000];
	char * revId;
	
	long int busPos = 0;
	long int revPos = 0;

	fgets(busLine, 259, busFp);
	busId = strtok(busLine, s);
	name = strtok(NULL, s);

	fgets(revLine, 6000, revFp);
	revId = strtok(revLine, s);

	long int busNextPos = ftell(busFp);
	long int revNextPos = ftell(revFp);

	YelpDataTree * root = CreateYelpDataTree(name, busPos, revPos, businesses_path, reviews_path);

	fseek(busFp, busNextPos, SEEK_SET);
	fseek(revFp, revNextPos, SEEK_SET);
	fgets(revLine, 6000, revFp);
	revId = strtok(revLine, s);
	revPos = revNextPos;
	revNextPos = ftell(revFp);

	while (!feof(busFp))
	{
		while (!stricmp(busId, revId)) // As long as the bus id and review id are the same
		{
			YelpDataTree * node = CreateYelpDataTree(name, busPos, revPos, NULL, NULL);
			YelpDataInsert(node, root, busFp, revFp);

			fseek(revFp, revNextPos, SEEK_SET);
			fgets(revLine, 6000, revFp);
			revId = strtok(revLine, s);
			revPos = revNextPos;
			revNextPos = ftell(revFp);
		}

		fseek(busFp, busNextPos, SEEK_SET);
		fgets(busLine, 259, busFp);
		busId = strtok(busLine, s);
		name = strtok(NULL, s);
		busPos = busNextPos;
		busNextPos = ftell(busFp);
	}

	fclose(busFp);
	fclose(revFp);

	return root;
}



static void TraverseInOrder(struct Business * b, BusinessPointerTree * root, char * zip_code, char * State, FILE * busFp, FILE * revFp)
{
	if (root == NULL)
		return; // BASE CASE

	const char s[2] = "\t";

	char * address;
	char * city;
	char * state;
	char * zipcode;

	fseek(busFp, root->businessPointer, SEEK_SET);
	char line[6000];
	fgets(line, 259, busFp);

	strtok(line, s);
	strtok(NULL, s);

	address = strtok(NULL, s);
	city = strtok(NULL, s);
	state = strtok(NULL, s);
	zipcode = strtok(NULL, s);

	TraverseInOrder(b, root->right, zip_code, State, busFp, revFp);

	if (zip_code == NULL || !stricmp(zipcode, zip_code))
	{
		if (State == NULL || !stricmp(state, State))
		{
			// Matches criteria
			if (b->num_locations)
			{
				if (b->locations[b->num_locations - 1].zip_code != NULL && !stricmp(zipcode, b->locations[b->num_locations - 1].zip_code))
				{
					if (b->locations[b->num_locations - 1].state != NULL && !stricmp(state, b->locations[b->num_locations - 1].state))
					{
						if (b->locations[b->num_locations - 1].city != NULL && !stricmp(city, b->locations[b->num_locations - 1].city))
						{
							if (b->locations[b->num_locations - 1].address != NULL && !stricmp(address, b->locations[b->num_locations - 1].address))
							{
								// Same as last node ---> Can combine them!
								b->locations[b->num_locations - 1].reviews = realloc(b->locations[b->num_locations - 1].reviews, sizeof(struct Review) * (b->locations[b->num_locations - 1].num_reviews + 1));

								char * stars;
								char * review;
								fseek(revFp, root->reviewPointer, SEEK_SET);
								char line[6000];
								fgets(line, 6000, revFp);

								strtok(line, s);

								stars = strtok(NULL, s);
								strtok(NULL, s);
								strtok(NULL, s);
								strtok(NULL, s);
								review = strtok(NULL, s);

								b->locations[b->num_locations - 1].num_reviews++;
								b->locations[b->num_locations - 1].reviews[b->locations[b->num_locations - 1].num_reviews - 1].stars = atoi(stars);
								b->locations[b->num_locations - 1].reviews[b->locations[b->num_locations - 1].num_reviews - 1].text = strdup(review);

								TraverseInOrder(b, root->left, zip_code, State, busFp, revFp);
								return;
							}
						}
					}
				}
			}
				if (!b->num_locations)
				{
					b->locations = malloc(sizeof(struct Location));
				}
				else
				{
					b->locations = realloc(b->locations, sizeof(struct Location) * (b->num_locations + 1));
				}
				b->num_locations++;
				b->locations[b->num_locations - 1].address = strdup(address);
				b->locations[b->num_locations - 1].city = strdup(city);
				b->locations[b->num_locations - 1].state = strdup(state);
				b->locations[b->num_locations - 1].zip_code = strdup(zipcode);
				b->locations[b->num_locations - 1].num_reviews = 1;

				b->locations[b->num_locations - 1].reviews = malloc(sizeof(struct Review));

				char * stars;
				char * review;
				fseek(revFp, root->reviewPointer, SEEK_SET);
				// char line[6000] has already been allocated at the beginning of the function!
				fgets(line, 6000, revFp);

				strtok(line, s);

				stars = strtok(NULL, s);
				strtok(NULL, s);
				strtok(NULL, s);
				strtok(NULL, s);
				review = strtok(NULL, s);

				b->locations[b->num_locations - 1].reviews[0].stars = atoi(stars);
				b->locations[b->num_locations - 1].reviews[0].text = strdup(review);
				
		}
	}

	TraverseInOrder(b, root->left, zip_code, State, busFp, revFp);
}

static YelpDataTree * NodeSearch(char * name, YelpDataTree * root)
{
	if (root == NULL)
		return NULL; // BASE CASE

	int comp = stricmp(name, root->name);
	if (comp == 0)
		return root; // WE FOUND THE NAME!
	else if (comp < 0)
		root = NodeSearch(name, root->left);
	else
		root = NodeSearch(name, root->right);

	return root;
}

static BusinessPointerTree * NodeStateSearch(char * State, BusinessPointerTree * root, FILE * busFp)
{
	if (root == NULL)
		return NULL; // BASE CASE

	const char s[2] = "\t";

	char * address;
	char * city;
	char * state;

	fseek(busFp, root->businessPointer, SEEK_SET);
	char line[259];
	fgets(line, 259, busFp);

	strtok(line, s);
	strtok(NULL, s);

	address = strtok(NULL, s);
	city = strtok(NULL, s);
	state = strtok(NULL, s);

	int comp = stricmp(State, state);
	if (comp == 0)
		return root; // WE FOUND THE STATE!
	else if (comp < 0)
		root = NodeStateSearch(State, root->left, busFp);
	else
		root = NodeStateSearch(State, root->right, busFp);

	return root;
}

static void StateSearch(struct Business * b, YelpDataTree * root, char * name, char * zipcode, char * state, FILE * busFp, FILE * revFp)
{
	TraverseInOrder(b, NodeStateSearch(state, root->locations, busFp), zipcode, state, busFp, revFp);
}

static void NullStateSearch(struct Business * b, YelpDataTree * root, char * name, char * zipcode, FILE * busFp, FILE * revFp)
{
	TraverseInOrder(b, root->locations, zipcode, NULL, busFp, revFp);
}

struct Business* get_business_reviews(struct YelpDataBST* bst,
	char* name, char* state, char* zip_code)
{
	FILE * busFp = fopen(bst->businessPath, "rb");
	FILE * revFp = fopen(bst->reviewPath, "rb");

	struct Business * business = malloc(sizeof(struct Business));
	business->name = strdup(name);
	business->num_locations = 0;

	YelpDataTree * tree = NodeSearch(name, bst);
	if (tree != NULL)
	{
		if (state == NULL)
		{
			NullStateSearch(business, tree, name, zip_code, busFp, revFp);
		}
		else
		{
			StateSearch(business, tree, name, zip_code, state, busFp, revFp);
		}
	}

	fclose(busFp);
	fclose(revFp);

	return business;
}

void destroy_business_result(struct Business* b)
{
	free(b->name);

	int i;
	for (i = 0; i < (int)b->num_locations; i++)
	{
		free(b->locations[i].address);
		free(b->locations[i].city);
		free(b->locations[i].state);
		free(b->locations[i].zip_code);

		int j;
		for (j = 0; j < (int)b->locations[i].num_reviews; j++)
		{
			free(b->locations[i].reviews[j].text);
		}
		free(b->locations[i].reviews);
	}
	if (b->num_locations)
		free(b->locations);
	free(b);
}