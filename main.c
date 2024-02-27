#include "pipex.h"

/*void	first_child(t_pipex *pipex)
{
	if (close(pipex->file1) == -1)
		ft_error("error close(file1)");
}*/

void	switch_fd(t_pipex *pipex)
{
	if (pipex->entry == -1)
	{
		if (dup2(pipex->file1, 0) == -1)
			ft_error(pipex, "error dup2(file1)");
	}
	else if (pipex->entry != 1)
	{
		if (dup2(pipex->entry, 0) == -1)
			ft_error(pipex, "error dup2(entry)");
	}
	if (pipex->last == 1)
	{
		if (dup2(pipex->file2, 1) == -1)
			ft_error(pipex, "error dup2(file2)");
	}
	else
	{ 
		if (dup2(pipex->fd[1], 1) == -1)
			ft_error(pipex, "error dup2(file1)");
	}	
}

void	cmd_child(t_pipex *pipex, char *arg, char **env)
{
	char	*o_path;
	char	**cmd;
//	int	test = -1;

	switch_fd(pipex);
	if (close(pipex->fd[0]) == -1)
		ft_error(pipex, "error close(fd[0])");
	if (close(pipex->fd[1]) == -1)
		ft_error(pipex, "error close(fd[1])");
	if (close(pipex->file1) == -1)
		ft_error(pipex, "error close(file1)");
	if (close(pipex->file2) == -1)
		ft_error(pipex, "error close(file2)");
	find_path(pipex, env, arg);
	o_path = check_path(pipex, env);
	cmd = ft_split(arg, ' ');
	if (execve(o_path, cmd, env) == -1)
	{
		free(o_path);
		free_tab(&cmd);
		ft_error(pipex, "error execve");
	}
	exit(0);
}


void	create_childs(t_pipex *pipex, int ac, char **av, char **env)
{
	int		y;
	int		id;

	y = 2;
	while(y < (ac - 1))
	{
		if (pipe(pipex->fd) == -1)
			ft_error(pipex, "error pipe");
		id = fork();
		if (id == -1)
		{
			ft_error(pipex, "error fork");
			close(pipex->fd[0]); //stop leak de fd
			close(pipex->fd[1]);
		}
		if (y == (ac - 2))
			pipex->last = 1;
		if (id == 0)
			cmd_child(pipex, av[y], env);
		pipex->entry = pipex->fd[0];
		close(pipex->fd[1]);
		y++;
	}
}

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
	pipex.file1 = open(av[1], O_RDONLY ); // permissions a mettre ?
	pipex.file2 = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (pipex.file1 == -1 || pipex.file2 == -1)
		ft_error(&pipex, "error open");
	create_childs(&pipex, ac, av, env);
}
