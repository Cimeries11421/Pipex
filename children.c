#include "pipex.h"

/*void	first_child(t_pipex *pipex)
{
	if (close(pipex->file1) == -1)
		ft_error("error close(file1)");
}*/



static void	switch_fd(t_pipex *pipex)
{
	dprintf(2, "fd = %d\n", pipex->fd[0]);
	if (pipex->entry == -1)
	{
		dup2(pipex->file1, 0);
		//	ft_error(pipex, "error dup2(file1)", 1);
	}
	else if (pipex->entry != -1)
	{
		dup2(pipex->entry, 0);
		//	ft_error(pipex, "error dup2(entry)", 1);
	}
	if (pipex->last == 1 && pipex->file2 != -1)
	{
		dup2(pipex->file2, 1);
//			ft_error(pipex, "error dup2(file2)", 1);
	}
	else
	{ 
		dup2(pipex->fd[1], 1);
//			ft_error(pipex, "error dup2(file1)", 1);
	}	
}

static void	cmd_child(t_pipex *pipex, char *arg, char **env)
{
	char	**cmd;

	cmd = NULL; // ?
	switch_fd(pipex);
	ft_close(pipex);
	if (pipex->entry != -1)
		close(pipex->entry);
	cmd = ft_split(arg, ' ');
	if (pipex->o_path != NULL)
	{
		if (execve(pipex->o_path, cmd, env) == -1)
		{
			//close 0 et 1 et 
			//if(close(pipex->entry) == -1)
			//	ft_error(pipex, "error close(file2)");
			free(pipex->o_path);
			cmd = free_tab(cmd);
			ft_error(pipex,"error execve", 1);
		}
	}
	exit(-1);
}


void	create_children(t_pipex *pipex, int ac, char **av, char **env)
{
	int		y;
	int		id;

	y = 2;
	while (y < (ac - 1))
	{
		if (pipe(pipex->fd) == -1)
			ft_error(pipex,"error pipe", 1);
		if (id == -1)
		{
			ft_error(pipex,"error fork", 1);
		}
		if (y == (ac - 2))
			pipex->last = 1;
		dprintf(2, "y = %d, av = %s\n", y, av[y]);
		analyse_path(pipex, av[y], env); //pas besoin de mettre o_path a null ?
		id = fork();
		if (id == 0)
			cmd_child(pipex, av[y], env);
		if (id != 0 && pipex->o_path != NULL)
			free(pipex->o_path);
		if (pipex->entry != -1)
			close(pipex->entry);// close l'ancien fd[0];
		pipex->entry = pipex->fd[0];
		close(pipex->fd[1]);
		y++;
	}
}
