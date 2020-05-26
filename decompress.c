#include<stdlib.h>
#include<string.h>
#include<stdio.h>


/*function to convert character to its binary form */
char* charToBinary(char ch){
	char *byte;
	int i = 0, rem, num = ch;
	
	byte = (char*)malloc(8);
	while(i < 8){
		byte[i] = '0';
		i++;
	}

	while(num != 0){
		rem = num % 2;
		num = num / 2;
		if(rem == 1)
			byte[i - 1] = '1';
		i--;
	}
	return byte;

}



/* Function to decompress the file, compressed using huffman algorithm */
void decompress1(int fd, int fwd)    {
    int count, i = 0, flag = 0;
    char ch, byte[8];
    inc_freq *freq_table;
	node *temp, root;

    /* first reads the no. of nodes */
    read(fd, &count, sizeof(int));
    // printf("%d\n", count);
    freq_table = (inc_freq*)malloc(sizeof(inc_freq) * count);
	
	while(i < count)	{
		read(fd, &freq_table[i], sizeof(freq_table[i]));
		// printf("%c: %d\n", freq_table[i].c, freq_table[i].freq);
		i++;
	}
	char *arr_c = (char *)malloc(sizeof(char) * count); 
	int *freq_c = (int *)malloc(sizeof(int) * count); 

	for(i = 0; i < count; i++)
		arr_c[i] = freq_table[i].c;
	
	for (i = 0; i < count; i++)
		freq_c[i] = freq_table[i].freq;

	//Calls the Huffman code funtion to generate the tree
	root = HuffmanCodes(arr_c, freq_c, count);

	/* for(i = 0; i < count; i++)	
		printf("%c: %s\n", arr_codes[i]->c, arr_codes[i]->ch_code);
	 */

	read(fd, &ch, 1);
	strcpy(byte, charToBinary(ch));
	i = 1;
	while(1)	{
		temp = &root;
		while(temp->left != NULL && temp->right != NULL)	{
			if(i == 8)	{
				if(!read(fd, &ch, 1))	{
					flag = 1;	//to indicate the end of the file
					break;
				}
				strcpy(byte, charToBinary(ch));
				i = 1;
			}
			if(byte[i] == '0')	{
				temp = temp->left;
				i++;
			}
			else if(byte[i] == '1')	{
				temp = temp->right;
				i++;
			}
		}
		if(flag)
			break;
		write(fwd, &temp->c, 1);
	}
}



/* Function to decompress the file, compressed using LZW algorithm */
void decompress2(int fd, int fwd)	{
	int i = 0, n = 0, len;
	short int oldcode, newcode;
	char c[50] = "", temp[50] = "", firstchar;
	read(fd, &n, sizeof(int));
	// dictionary di[n];
	list table;
	init(&table);
	code_table d, di[n];

	/* To initialize the dictionary with the unique characters */
	for(i = 0; i < n; i++)	{
		read(fd, &di[i], sizeof(di[i]));
		strcpy(d.c, di[i].c);
		d.index = di[i].index;
		append(&table, d);
	}

	read(fd, &oldcode, sizeof(short int));
	strcpy(temp, searchstring_index(&table, oldcode));
	write(fwd, temp, strlen(temp));

	while(read(fd, &newcode, sizeof(short int)))	{
		if(search_index(&table, newcode) == 0)	{
			strcpy(c, searchstring_index(&table, oldcode));
			len = strlen(c);
			// strcpy(c, temp);
			c[len] = firstchar;
			c[len + 1] = '\0';
		}
		else	{
			
			strcpy(c, searchstring_index(&table, newcode));
			len = strlen(c);
			// strcpy(c, temp);
			c[len] = '\0';
		}

		write(fwd, c, strlen(c));
		firstchar = c[0];

		if(table.size < 4096)	{
			strcpy(temp, searchstring_index(&table, oldcode));
			len = strlen(temp);
			strcpy(d.c, temp);
			d.c[len] = firstchar;
			d.c[len + 1] = '\0';
			d.index = n++;
			append(&table, d);
		}
		oldcode = newcode;
	}

	// traverse(table);
}