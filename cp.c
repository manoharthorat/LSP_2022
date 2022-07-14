#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char ** argv)
{
	if(argc != 3)
	{
		printf("%s <file to be copy> <file to be paste>\n",argv[0]);
		exit(EXIT_FAILURE);
	}

	// Open the existing file in read mode
	int fd = open(argv[1], O_RDONLY);
	if( fd < 0 )
	{
		perror("open ");
		goto clean;
	}

	// Create a file to copy the data 
	int fd2 = creat(argv[2], 0666);
	if(fd2 < 0)
	{
		perror("creat ");
		goto clean;
	}


	char buff[BUFSIZ] = {0};
	ssize_t cnt = 0;
	// Read the data from file
	while((cnt = read(fd, buff, BUFSIZ)) > 0)
	{
		//Write the data in to the file 
		ssize_t cnt2 = write(fd2, buff, cnt);
		if(cnt2 < 0)
		{
			perror("write ");
			goto clean;
		}

	}
	if(cnt <= 0)
	{
		perror("read ");
		goto clean;
	}

//clean up code 
clean:
	close(fd);
	close(fd2);
	exit(EXIT_FAILURE);
}
