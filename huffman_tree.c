#include"huffman_tree.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/* Function to create newnode for the minheap */
node *newnode(char data, unsigned freq)    {
	node *temp = (node*)malloc(sizeof(node));
	temp->c = data;
	temp->frequency = freq;
	temp->left = temp->right = NULL;
	return temp;
}

/* Function to swap nodes */
void swapnode(node **a, node **b)   {
	node *temp = *a;
	*a = *b;
	*b = temp;
}

/* Function to check if the size of minheap becomes one */
int isSizeOne(minheap *a)   {
	return (a->size == 1);
}

/* Function to insert newnode(i.e. the subtree) into the meanheap */
void insertintominheap(minheap *a, node *inode) {
	a->size++;
	int i = a->size - 1;
	a->arr[i] = inode;
	sortminheap(a);
}

/* Function to sort the minheap in increasing order of frequency */
void sortminheap(minheap *a)    {
	int i = 0, minidx = 0, j = 0;
	for(i = 0; i < a->size; i++)    {
		minidx = i;
		for(j = i; j < a->size; j++)    {
			if(a->arr[j]->frequency < a->arr[i]->frequency) {
				minidx = j;
			}
		}
		if(minidx != i) {
			swapnode(&a->arr[i], &a->arr[minidx]);
		}
	}
}

/* Function to check if the node is a leaf node */
int isLeaf(node *root)  {
	return (!(root->left) && !(root->right));
}

/* Function to return the lowest frequency node */
node * extractminnode(minheap *a)   {
	node *temp = a->arr[0];
	shiftminheap(a);
	return temp;
}

/* Function to shift the nodes to the left */
void shiftminheap(minheap *a)   {
	if(a->size == 1)    {
		a->size--;
		return;
	}
	int i = 0;
	//  node *temp = NULL;
	for(i = 0; i < a->size - 1; i++)    {
		a->arr[i] = a->arr[i + 1];
	}
	a->size--;
	//  free(temp);
}


/* Function to create minheap of given size */
minheap *createminheap(unsigned capacity)   {
	minheap *newminheap = (minheap*)malloc(sizeof(minheap));
	newminheap->capacity = capacity;
	newminheap->size = 0;
	newminheap->arr = (node **)malloc(sizeof(node*) * capacity);
	return newminheap;
}

/* Function to createminheap */
minheap *creatandbuildminheap(char *data, int *freq, int size)   {
	minheap *newminheap = createminheap(size);
	int i = 0;
	for(i = 0; i < size; i++)   {
		// printf("data is: %c, freq is: %d\n", data[i], freq[i]);
		newminheap->arr[i] = newnode(data[i], freq[i]);
		// printf("newminheap->arr[i]->data: %c, newminheap->arr[i]->frequency: %d\n", newminheap->arr[i]->c, newminheap->arr[i]->frequency);
	}
	newminheap->size = size;
	// printf("minheap->size = %d\n", newminheap->size);
	return newminheap;
}

/* Funtion to build huffman tree */
node *buildhuffmantree(char *data, int *freq, int size)  {
	node *left = NULL, *right = NULL, *top = NULL;

	minheap *newminheap = creatandbuildminheap(data, freq, size);
	while(!isSizeOne(newminheap))    {
		left = extractminnode(newminheap);
		right = extractminnode(newminheap);

		top = newnode('\0', left->frequency + right->frequency);
		top->left = left;
		top->right = right;
		insertintominheap(newminheap, top);
	}
	return(extractminnode(newminheap));
}

/* Funtion to generate huffmancodes */
node HuffmanCodes(char data[], int freq[], int size)    { 
	// Construct Huffman Tree 
	node* root = buildhuffmantree(data, freq, size); 

	/* Print Huffman codes using 
	 * the Huffman tree built above 
	 */
	int arr[MAX_TREE_HT], top = 0; 
	printCodes(root, arr, top);
	
	return *root;
	
} 


/* Function to printcodes */
void printCodes(node* root, int arr[], int top) {
	char *code;
	storecode *newcode;
	// Assign 0 to left edge and recur
	if (root->left) { 
		arr[top] = 0; 
		printCodes(root->left, arr, top + 1); 
	} 
	// Assign 1 to right edge and recur
	if (root->right) { 
		arr[top] = 1; 
		printCodes(root->right, arr, top + 1); 
	} 
	/*If this is a leaf node, then 
	 *it contains one of the input 
	 *characters, store the character 
	 *and its code from arr[] 
	 */
	if (isLeaf(root)) { 
		code = printArr(root->c, arr, top); 
		newcode = store(root->c, code, top);
		storecodes(newcode);
	}
}


/* Funtion to print an array */
char* printArr(char c, int arr[], int n) { 
	int i;
	char *code = (char*)malloc(sizeof(char) * n);
	for(i = 0; i < n; i++)	{
		code[i] = (char)(arr[i] + 48);
	}
	code[i] = '\0';
	return code;
}


/* Function to store codes of the characters */
storecode* store(char c, char *code, int n) {
	storecode *newcode = (storecode*)malloc(sizeof(storecode));
	newcode->c = c;
	newcode->ch_code = code;
	return newcode;
}


/* Funtion to store character and its respective code into an array */
void storecodes(storecode *newcode)	{
	static int i = 0;
	if(i == 0)	{
		arr_codes = (storecode**)malloc(sizeof(storecode*) * 150);
	}
	arr_codes[i] = (storecode*)malloc(sizeof(storecode));
	arr_codes[i]->c = newcode->c;
	arr_codes[i]->ch_code = newcode->ch_code;
	i++;
}