#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

void	main(void)
{
	int fd = open("test.txt", O_WRONLY| O_CREAT, 0777);
	dup2(fd, 1);
	printf("coucou");
}
