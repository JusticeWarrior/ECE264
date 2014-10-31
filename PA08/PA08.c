#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "answer08.h"

static void List_print(List * list)
{
	List * tail = list;
	while (tail != NULL) {
		printf("\"%s\" ==> ", tail->str);
		tail = tail->next;
	}
	printf("NULL");
}

int main(int argc, char * * argv)
{
	char * testStrings[] = { "test1", "test2", "test3", "test4", "test5", "test6", "test7", "test8", "test9" };
	List* node1 = List_createNode(testStrings[0]);
	List* node2 = List_createNode(testStrings[1]);
	List* node3 = List_createNode(testStrings[2]);
	List* node4 = List_createNode(testStrings[3]);
	List* node5 = List_createNode(testStrings[4]);
	List* node6 = List_createNode(testStrings[5]);
	List* node7 = List_createNode(testStrings[6]);
	List* node8 = List_createNode(testStrings[7]);
	List* node9 = List_createNode(testStrings[8]);

	// List 1
	List* list1 = node1;
	node1->next = node2;
	node2->next = node6;
	node6->next = node5;
	node5->next = node4;
	node4->next = node3;

	// List 2
	List* list2 = node8;
	node8->next = node9;
	node9->next = node7;

	int length1 = List_length(list1);
	int length2 = List_length(list2);

	if (length1 != 6)
		return EXIT_FAILURE; // List 1 not = 6
	if (length2 != 3)
		return EXIT_FAILURE; // List 2 not = 3

	list1 = List_sort(list1, strcmp);
	list2 = List_sort(list2, strcmp);

	List_print(list1);
	fprintf(stdout, "\n");
	List_print(list2);
	fprintf(stdout, "\n\n");

	List* combinedLists = List_merge(list1, list2, strcmp);
	List_print(combinedLists);

	List_destroy(combinedLists);

	return EXIT_SUCCESS;
}