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

/**
* When provided two lists, the function determines which list is 
* NULL and returns the opposite list.
*/
static List * Null_List(List * lhs, List * rhs)
{
	if (lhs == NULL)
	{
		return rhs;
	}
	else
	{
		return lhs;
	}
}

/**
* When provided two pointers to nodes and a comparision function, the function determines which node
* is larger, moves its position to be the next in the list and returns the larger node.
*/
static List * CompareNodes(List ** lhs, List ** rhs, int(*compar)(const char *, const char*))
{
	if (compar((*lhs)->str, (*rhs)->str) >= 0)
	{
		List * larger = *rhs;
		*rhs = (*rhs)->next;
		return larger;
	}
	else
	{
		List * larger = *lhs;
		*lhs = (*lhs)->next;
		return larger;
	}
}

List * List_merge(List * lhs,
	List * rhs,
	int(*compar)(const char *, const char*))
{
	List * head = NULL;
	List * tail = head;

	if (lhs != NULL && rhs != NULL)
	{
		head = CompareNodes(&lhs, &rhs, compar);
	}
	else
	{
		return Null_List(lhs, rhs);
	}

	while (lhs != NULL && rhs != NULL)
	{
		tail->next = CompareNodes(&lhs, &rhs, compar);
		tail = tail->next;
	}

	tail->next = Null_List(lhs, rhs);
	return head;
		
}

List * List_sort(List * list, int(*compar)(const char *, const char*))
{
	return NULL;
}