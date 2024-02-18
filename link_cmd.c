#include "pipex.h"

/*void	link(t_pipex pipex)
{
	int	fd;

	if	(pipe(fd) == -1)
	{
		write(2, "error : pipe\n", 13);
		//fonction free
		exit(1);
	}
}
*/
int	main(int ac, char **av, char **env)
{
	t_pipex	pipex;

/*	if (ac != 5) //perror ?
		return (-1);*/
	pipex.n_arg = ac;
	pipex.arg = av;
	find_path(&pipex, env);
	check_path(&pipex, env);
	return (0);
}
