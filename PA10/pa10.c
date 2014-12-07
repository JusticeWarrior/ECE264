#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "answer10.h"

int main(int argc, char * * argv)
{
	struct YelpDataBST * tree = create_business_bst("/home/shay/a/ece264p0/share/yelp_data/businesses.tsv", "/home/shay/a/ece264p0/share/yelp_data/reviews.tsv");
	//struct Business * business = get_business_reviews(tree, "Meatballz", "NV", NULL);

	//destroy_business_bst(tree);

	//destroy_business_result(business);

	return EXIT_SUCCESS;
}
