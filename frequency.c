#include"frequency.h"
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include<errno.h>
#include<limits.h>

/* count frequency of the characters from the file */
inc_freq * count_freq(int fd)	{
	char c;
	int i = 0, n = 0;
	
	lseek(fd, 0, SEEK_SET);
	
	//structure which stores the character as well as the frequency
	inc_freq *arr = (inc_freq*)malloc(sizeof(inc_freq) * 150);
	
	int farr[256] ; //This array will calculate different characters and their frequency  using hashing
	
	for( i=0;i<256;i++){
		farr[i]=0;	// Initialize frequency of every character to 0 
	}	
		

	int count_ch = 0;
	while(read(fd, &c, 1))	{
		count_ch++;
		
		farr[c]++;	// This line will increment frequency of character c , hashing is used
	}
	
	
	// below for loop is to copy different characters from farr  to structure which stores frequency 
	
	for( i=0;i<256;i++){
		// If farr[i] is not 0 that means character i is present in text file 
		// so we will set arr[n].c=i and frequency of i will be farr[i]
		// therefore we set frequency of c i.e arr[n].freq =farr[i] 
		
		if(farr[i]!=0){
			arr[n].c=i;
			arr[n].freq=farr[i];
			n++;
		}
	}
	
	arr[n].freq = INT_MAX;
	
	sort_struct(arr, n);
	return arr;

}

/* sorting the characters according to increasing frequency (uses selection sort) */
void sort_struct(inc_freq *s, int len)	{
	int i = 0, j = 0, min_idx, temp;
	char ctemp;
	for (i = 0; i < len - 1; i++)	{
		// Last i elements are already in place    
		
		min_idx = i;  
		for (j = i+1; j < len; j++)  {
			if (s[j].freq < s[min_idx].freq)  
				min_idx = j; 
		}

		if(min_idx != i)	{
			//swaping the frequencies
			temp = s[min_idx].freq;
			s[min_idx].freq = s[i].freq;
			s[i].freq = temp;
			//swaping characters
			ctemp = s[min_idx].c;
			s[min_idx].c = s[i].c;
			s[i].c = ctemp;

			
		}
		
	}

}

/* Function to print the frequency table */
void print_freq(inc_freq *a, int n)	{
	int i = 0;
	for(i = 0; i < n; i++)	{
		printf("%c - %d\n", a[i].c, a[i].freq);
	}
}

/* Function which returns the array of unique characters from the file */
char * arr_char(int fd)   {
	char c, *arr_c;
	arr_c = (char*)malloc(sizeof(char) * 150);
	int count = 0, i = 0;

	//reading first character from the file
	read(fd, &c, sizeof(char));
	arr_c[i++] = c;

	//storing all the unique characters in the file
	while(read(fd, &c, sizeof(char)))   {
		count++;
		for(i = 0; i < strlen(arr_c); ) {
			if(arr_c[i++] == c)
				break;
		}    

		/*checks if i reaches the end, meaning it found no element matching the extracted character
		 *Also there can be such case where the string ends with that character and then it repeats again
		 *then we will have to check if the last element of the array equals the character
		 */
		if(i == count && arr_c[count - 1] != c)	{
			arr_c[count] = c;
		}
		else	{
			count--;	//Decreasing by 1 so that we can store in continuation
		}
	}
	//making a string 
	arr_c[count + 1] = '\0';

	//returning the unique character array
	return arr_c;
}
