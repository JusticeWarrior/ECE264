#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "answer09.h"

int main(int argc, char * * argv)
{
	BusinessNode * root = create_node("5.0", "random name", "random address");
	root->left = create_node("3.5", "another name", "another address");
	root->right = create_node("4.0", "yet another name", "some address");
	root->left->right = create_node("1.5", "name 3", "address 3");

	BusinessNode * search = tree_search_name("another name", root);
	fprintf(stdout, "Search for \"another name\":\n");
	print_node(search);
	fprintf(stdout, "\n");
	if (search == NULL)
		return EXIT_FAILURE;

	fprintf(stdout, "First Tree:\n");
	print_tree(root);
	fprintf(stdout, "\n\n");

	destroy_tree(root);

	BusinessNode * shortFile = load_tree_from_file("shortfile.tsv");

	search = NULL;
	search = tree_search_name("Culver's", root);
	fprintf(stdout, "Search for \"Culver's\":\n");
	print_node(search);
	fprintf(stdout, "\n");
	if (search == NULL)
		return EXIT_FAILURE;

	fprintf(stdout, "Second Tree:\n");
	print_tree(shortFile);
	fprintf(stdout, "\n\n");

	destroy_tree(shortFile);

	// MAKE SURE IT IS CORRECT FROM HERE!! OTHERWISE YOU WILL HAVE TO PRINT ALL RESULTS OUT!
	BusinessNode * longFile = load_tree_from_file("yelp_businesses.tsv");

	search = NULL;
	search = tree_search_name("Rusconi's American Kitchen", root);
	fprintf(stdout, "Search for \"Rusconi's American Kitchen\":\n");
	print_node(search);
	fprintf(stdout, "\n");
	if (search == NULL)
		return EXIT_FAILURE;

	fprintf(stdout, "Third Tree:\n");
	print_tree(longFile);
	fprintf(stdout, "\n");

	destroy_tree(longFile);

	return EXIT_SUCCESS;

}