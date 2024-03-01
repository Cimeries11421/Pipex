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
	pipex.entry = -1;
	pipex.last = 0;
	pipex.file1 = open(av[1], O_RDONLY ); // permissions a mettre ?
	pipex.file2 = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (pipex.file1 == -1 || pipex.file2 == -1)
		ft_error(&pipex, "error open", 0); // close file 1 ou 2 ?
	create_children(&pipex, ac, av, env);
	close(pipex.entry); //secure
	close(pipex.file1);	
	close(pipex.file2);
	while (wait(NULL) > 0)
	{
		write(2, "enfant mort\n", 12);
	}
	write(2,"fini", 4);
}
