#include"frequency.h"
#include"huffman_tree.h"
#include"list.h"
#include"compress.c"
#include"decompress.c"
#include<limits.h>
#include<errno.h>

int main(int argc, char *argv[])    {
	int fd, fwd;

	/* Making a check for the number of arguements */
	if(argc < 4)    {
		printf("Too few arguements:\n");
		return EINVAL;
	}

	fd = open(argv[2], O_RDONLY);
	/* Checking for the file opening or not */
	if(fd == -1) {
		printf("Unable to open file:");
		return EINVAL;
	}

	fwd = open(argv[3], O_RDWR | O_CREAT, S_IWUSR | S_IRUSR);
	/* Checking if the file was created or not */
	if(fd == -1)	{
		printf("Unable to create file:");
		return EINVAL;
	}

	/* If the command is to compress the file */
	if(strcmp(argv[1], "-c1") == 0)	{
		compress1(fd, fwd);
	}
	else if(strcmp(argv[1], "-c2") == 0)	{
		compress2(fd, fwd);
	}
	
	/* If the command is to decompress the file */
	else if(strcmp(argv[1], "-uc1") == 0)	{
		decompress1(fd, fwd);
	}
	else if(strcmp(argv[1], "-uc2") == 0)	{
		decompress2(fd, fwd);
	}

	/* If the command is wrong */
	else	{
		perror("Wrong arguements:");
		return EINVAL;
	}
	
	close(fd);
	close(fwd);
	return 0;
}