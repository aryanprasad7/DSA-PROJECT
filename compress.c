#include<stdio.h>
#include<stdlib.h>

#include<sys/types.h>
#include<sys/stat.h>

#include<math.h>
#include<string.h>
#include<limits.h>
#include<unistd.h>
#include<fcntl.h>

/* Funtions in this file */
char binToChar(char *byte);
void createfile(int fd, int fwd, int size);
void compress1(int fd, int fwd);
void compress2(int fd, int fwd);
	
/* Function to convert binary code to character */
char binToChar(char *byte){
	int i, sum = 0;
	char ch;

	/* This loop converts the byte array of binary to its corresponding decimal value */
	for(i = 0;i < 7 ;i++){
		sum = sum + (pow(2, i) * (byte[7 - i] - '0'));
	}

	ch = sum;
	return ch;
}

/* Function to create new file i.e. the compressed file */
void createfile(int fd, int fwd, int size){
	char ch, code;
	int i = 0, j = 0, count = 1;
	char byte[8];
	byte[0] = '0';
	lseek(fd, 0, SEEK_SET);
	
	while(read(fd, &ch, 1))	{
		i = 0;
		while(i < size)	{
			if(ch == arr_codes[i]->c)	{
				j = 0;
				while(arr_codes[i]->ch_code[j] != '\0')	{
					// If the count of the byte is code is equal to 8, then form a character
					if(count == 8)	{
						code = binToChar(byte);
						write(fwd, &code, 1);
						bzero(byte, 8);
						byte[0] = '0';
						count = 1;
					}
					byte[count] = arr_codes[i]->ch_code[j];
					count++;
					j++;
				}
				break;
			}
			i++;
		}
	}

	// If the count of the byte is not equal to 8
	if(count != 8)	{
		while(count < 8)	{
			byte[count] = '0';
			count++;
		}
		code = binToChar(byte);
		write(fwd, &code, 1);
	}
}



/* Function to compress the file using huffman algorithm */
void compress1(int fd, int fwd){
	char c;
	/* If the file is already empty, no need to compress */
	if(!read(fd, &c, 1))
		return;
	lseek(fd, 0, SEEK_SET);

	/* Calling the count_freq function to calculate the frequency of each character */
	inc_freq *arr = count_freq(fd);
	int size_of_arr = 0, i = 0;
	node temp;
	for(i = 0; arr[i].freq != INT_MAX; i++)	{
		size_of_arr++;		
	}

	/* printing the sorted structure
	print_freq(arr, size_of_arr); */

	char *arr_c = (char *)malloc(sizeof(char) * size_of_arr); 
	int *freq_c = (int *)malloc(sizeof(int) * size_of_arr); 

	for(i = 0; i < size_of_arr; i++)
		arr_c[i] = arr[i].c;
	
	for (i = 0; i < size_of_arr; i++)
		freq_c[i] = arr[i].freq;
	
	temp = HuffmanCodes(arr_c, freq_c, size_of_arr);
	
	/* for(i = 0; i < size_of_arr; i++)	{
		printf("%c: %s\n", arr_codes[i]->c, arr_codes[i]->ch_code);
	} */

	write(fwd, &size_of_arr, sizeof(int));
	for(i = 0; i < size_of_arr; i++)    {
		write(fwd, &arr[i], sizeof(arr[i]));
	}
	/* now we have array of codes namely: arr_codes that we need to 
	 * write in the file by comparing the respective alphabet in 
	 * the file 
	 */
	createfile(fd, fwd, size_of_arr);
}



/* Function to compress the file using LZW compression */
void compress2(int fd, int fwd) {
	char c;
	/* If the file is already empty, no need to compress */
	if(!read(fd, &c, 1))
		return;
	lseek(fd, 0, SEEK_SET);

	char *arr_c = arr_char(fd);		//this array stores the array of unique characters from the file
	char ch[100] = "", temparr[100] = "";
	int n = strlen(arr_c), len;
	short int i = 0;
	// printf("%d\n", n);
	
	list table;		//to store the dictionary
	init(&table);
	code_table d, dn[n];

	for(i = 0; i < n; i++)	{
		d.c[0] = arr_c[i];
		d.c[1] = '\0';
		d.index = i;
		append(&table, d);
		strcpy(dn[i].c, d.c);
		dn[i].index = d.index;
	}

	// writing the unique character length in the file
	write(fwd, &n, sizeof(int));

	// writing the unique character array dictionary in the file;
	for(i = 0; i < n; i++)
		write(fwd, dn + i, sizeof(dn[i]));		// writing the structure of unique dictionary in the file
	
	lseek(fd, 0, SEEK_SET);
	ch[0] = '\0';
	temparr[0] = '\0';

	while(read(fd, &c, 1))	{
		
		strcpy(ch, temparr);
		len = strlen(temparr);
		ch[len] = c;
		ch[len + 1] = '\0';

		/* If the ch string is not present in the table  
		 * then add it to the dictionary
		 */
		if(!search(&table, ch))	{
			/* ONLY add when the size of the table < 4096 */
			if(table.size < 4096)	{
				strcpy(d.c, ch);
				d.index = n++;
				append(&table, d);
			}
			/* Seachting for the string in the dictionary
			 * and writing its index in the file
			 */
			i = searchindex(&table, temparr);
			write(fwd, &i, sizeof(short int));

			/* copying the character c to the temp string */
			temparr[0] = c;
			temparr[1] = '\0';
		}

		/* if the string ch is present in the dictionary
		 * then make temparr string = ch
		 */
		else	{
			strcpy(temparr, ch);
			temparr[strlen(temparr)] = '\0';
		}
	}

	/* Writing the last character in the table */
	i = searchindex(&table, temparr);
	if(i != -1)
		write(fwd, &i, sizeof(short int));
	
	// traverse(table);

}
