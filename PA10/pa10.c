#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "answer10.h"

int main(int argc, char * * argv)
{
	struct YelpDataBST * tree = create_business_bst("businesses.tsv", "reviews.tsv");

	struct Business * business = get_business_reviews(tree, "Boston Cleaners", "NV", NULL);

	business->locations->reviews[0];
	business->locations->reviews[1];
	business->locations->reviews[2];
	business->locations->reviews[3];
	business->locations->reviews[4];
	business->locations->reviews[5];
	business->locations->reviews[6];
	business->locations->reviews[7];
	business->locations->reviews[8];
	business->locations->reviews[9];
	business->locations->reviews[10];
	business->locations->reviews[11];

	business->locations[1];
	business->locations[1].reviews[0];
	business->locations[1].reviews[1];
	business->locations[1].reviews[2];
	business->locations[1].reviews[3];

	destroy_business_bst(tree);

	destroy_business_result(business);
}