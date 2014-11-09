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

	print_tree(root);

	BusinessNode * shortFile = load_tree_from_file("shortfile.tsv");



	return EXIT_SUCCESS;

}