/* This structure stores the character along with its frequency */
typedef struct inc_freq	{
	char c;
	int freq;
}inc_freq;

/* sorting the characters according to increasing frequency */
void sort_struct(inc_freq *s, int len);

/* count frequency of the characters from the file */
inc_freq * count_freq(int);

/* Function which returns the array of unique characters from the file */
char * arr_char(int);

/* Funtion to print the frequency table */
void print_freq(inc_freq *, int);