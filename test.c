#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

void	main(void)
{
	int	file = open("coucou.txt", O_WONLY);

	dup2(file, 1);
}
