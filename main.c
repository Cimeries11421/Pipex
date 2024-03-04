#include "pipex.h"

int		main(int ac, char **av, char **env)
{
	t_pipex		pipex;

	if (ac < 5)
	{
		write(1, "error : too few arguments\n", 25);
		exit(-1);
	}
	pipex.path = NULL;
	pipex.o_path = NULL; //pas oublier de free a chaque fois
	pipex.entry = -1;
	pipex.last = 0;
	pipex.file1 = open(av[1], O_RDONLY ); // permissions a mettre ?
	pipex.file2 = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (pipex.file1 == -1)
	{
		perror(av[1]);
		pipex.file1 = open("/dev/null", O_RDONLY, 0666); //permission ?
	}
	if (pipex.file2 == -1)
			perror(av[ac - 1]);
	dprintf(2, "file1 = %d\n", pipex.file1);
	dprintf(2, "file2 = %d\n", pipex.file2);
	create_children(&pipex, ac, av, env);
	close(pipex.entry); //secure
	close(pipex.file1);	
	close(pipex.file2);
	while (wait(NULL) > 0);
}
