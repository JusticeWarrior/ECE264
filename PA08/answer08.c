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


static void Append_Lists(List * lhs, List * rhs, List * tail)
{
	if (lhs == NULL)
	{
		tail->next = rhs;
		return;
	}
	else
	{
		tail->next = lhs;
		return;
	}
}

List * List_merge(List * lhs,
	List * rhs,
	int(*compar)(const char *, const char*))
{
	List * head = NULL;
	List * tail = NULL;

	if (lhs != NULL && rhs != NULL)
	{
		if (compar(lhs->str, rhs->str) >= 0)
		{
			head = rhs;
			rhs = rhs->next;
			tail = head;
		}
		else
		{
			head = lhs;
			lhs = lhs->next;
			tail = head;
		}
	}
	else
	{
		Append_Lists(lhs, rhs, tail);
		return head;
	}

	List * current;

	while (lhs != NULL && rhs != NULL)
	{
		if (compar(lhs->str, rhs->str) >= 0)
		{
			current = rhs;
			rhs = rhs->next;
		}
	}

	Append_Lists(lhs, rhs, tail);
	return head;
		
}

List * List_sort(List * list, int(*compar)(const char *, const char*))
{
	return NULL;
}