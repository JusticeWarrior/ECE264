#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "answer08.h"

List * List_createNode(const char * str)
{
	List * list = malloc(sizeof(List));

	list->str = strdup(str);
	list->next = NULL;

	return list;
}

void List_destroy(List * list)
{
	if (list != NULL)
	{
		free(list->str);
		free(list);
	}
}

int List_length(List * list)
{
	int count = 0;
	while (list != NULL)
	{
		list = list->next;
		count++;
	}

	return count;
}

List * List_merge(List * lhs,
	List * rhs,
	int(*compar)(const char *, const char*))
{
	List * head = lhs;

	// Find the tail node
	while (lhs->next != NULL)
	{
		lhs = lhs->next;
	}
	// Link the tail to the head of the right hand side
	lhs->next = rhs;

	// return the head of the left hand side
	return head;
}

List * List_sort(List * list, int(*compar)(const char *, const char*))
{
	return NULL;
}