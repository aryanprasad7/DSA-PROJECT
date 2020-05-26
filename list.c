#include<stdio.h>
#include<stdlib.h>
#include"list.h"

//Function to initialize the list
void init(list *l)  {
	l->size = 0;
	l->head = NULL;
	l->tail = NULL;
}

//Function to append an element to the list
void append(list *l, code_table d) {
	listnode * newnode = (listnode*)malloc(sizeof(listnode));
	newnode->t = d;
	newnode->next = NULL;
	listnode *ptr = l->tail;
	if(!ptr)    {
		l->head = newnode;
		l->tail = newnode;
		l->size++;
		return;
	}
	ptr->next = newnode;
	l->tail = newnode;
	l->size++;
}

//Function to traverse the list
void traverse(list l)   {
	listnode *ptr = l.head;
	printf("index\tstring\n");
	while(ptr)    {
		printf("%d\t%s\n", ptr->t.index, ptr->t.c);
		ptr = ptr->next;
	}
}

/* function returns 1 if the string is found in the table 
 * orelse returns 0 if not found
 */
int search(list *l, char *str)	{
	listnode* ptr = l->head;
	while(ptr)	{
		if(strcmp(ptr->t.c, str) == 0)	{
			return 1;
			break;
		}
		ptr = ptr->next;
	}
	return 0;
}

//Function to search index of the given string in the list, returns -1 if not in the list
int searchindex(list *l, char *str)	{
	listnode *ptr = l->head;
	while(ptr)	{
		if(strcmp(ptr->t.c, str) == 0)	{
			return ptr->t.index;
			break;
		}
		ptr = ptr->next;
	}
	return -1;
}

//Function to search for the string at index i
char *searchstring_index(list *l, int n)	{
	int i = 0; 
	listnode *ptr = l->head;
	for(i = 0; i < n ; i++)	{
		/* if(ptr->t.index == n)	{
			return ptr->t.c;
		} */
		ptr = ptr->next;
	}
	return ptr->t.c;
}

short int search_index(list *l, int n)	{
	short int i = 0;
	listnode *ptr = l->head;
	while(ptr)	{
		if(ptr->t.index == n)	{
			i = 1;
		}
		ptr = ptr->next;
	}
	return i;
}