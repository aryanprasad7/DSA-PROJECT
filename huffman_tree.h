#define MAX_TREE_HT 150


/* This constitutes one node of the tree */
typedef struct node {
    char c;
    unsigned frequency;
    struct node *left, *right;
}node;

typedef struct minheap  {
    int size;
    unsigned int capacity;
    node **arr;
}minheap;

/* Structure to store the code of the character in string representation */
typedef struct storecode    {
    char c;
    char *ch_code;
}storecode;

storecode **arr_codes;      /* stores the character along with its code */

/* Function to sort the minheap in increasing order of frequency */
void sortminheap(minheap *a);
/* Function to check if size of the minheap becomes one */
int isSizeOne(minheap *a);
/* Function to return the lowest frequency node */
node* extractminnode(minheap *a);
/* Function to check if the node is a leaf node */
int isLeaf(node *);
/* Function to swap nodes */
void swapnode(node **a, node **b);
/* Function to create newnode for the minheap */
node * newnode(char data, unsigned freq);
/* Function to printcodes */
void printCodes(node* root, int arr[], int top);
/* Function to insert newnode(i.e. the subtree) into the meanheap */
void insertintominheap(minheap *a, node *inode);
/* Function to shift the nodes to the left */
void shiftminheap(minheap *a);
/* Function to create minheap of given size */
minheap *createminheap(unsigned capacity);
/* Function to createminheap */
minheap *creatandbuildminheap(char *data, int *freq, int size);
/* Funtion to build huffman tree */
node *buildhuffmantree(char *data, int *freq, int size);
/* Funtion to print an array */
char* printArr(char c, int arr[], int n);
/* Funtion to generate huffmancodes */
node HuffmanCodes(char data[], int freq[], int size);
/* Function to store codes of the characters */
storecode* store(char c, char *code, int n);
/* Funtion to store character and its respective code into and array */
void storecodes(storecode *newnode);