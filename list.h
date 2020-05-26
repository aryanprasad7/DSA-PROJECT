#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<errno.h>
#include<unistd.h>
#include<fcntl.h>

/* Structure to store the character and its index */
typedef struct code_table	{
	char c[50];
	short int index;
}code_table;

/* Node to a list */
typedef struct listnode {
    code_table t;
    struct listnode* next;
}listnode;

/* Structure list */
typedef struct list	{
	int size;
	listnode *head, *tail;
}list;

/* typedef struct dict	{
	short int index;
	char c[50];
}dictionary; */

//Function to initialize the list
void init(list *l);

//Function to append an element to the list
void append(list *l,code_table d);

//Function to traverse the list
void traverse(list l);

/* function returns 1 if the string is found in the table 
 * orelse returns 0 if not found
 */
int search(list *l, char *str  );

//Function to search index of the given string in the list, returns -1 if not in the list
int searchindex(list *l, char *str);

//Function to search for the string at index i
char *searchstring_index(list *l, int n);

//returns if the index is present in the dictionary or not
short int search_index(list *l, int n);