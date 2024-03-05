#include "pipex.h"

/*void	first_child(t_pipex *pipex)
{
	if (close(pipex->file1) == -1)
		ft_error("error close(file1)");
}*/



static void	switch_fd(t_pipex *pipex, int id)
{
	dprintf(2, "fd = %d\n", pipex->fd[0]);
	if (pipex->entry == -1)
	{
		if (dup2(pipex->file1, 0) == -1)
			ft_error(pipex, "error dup2(file1)", 1, id);
	}
	else if (pipex->entry != -1)
	{
		if (dup2(pipex->entry, 0) == -1)
			ft_error(pipex, "error dup2(entry)", 1, id);
	}
	if (pipex->last == 1 && pipex->file2 != -1)
	{
		if (dup2(pipex->file2, 1) == -1)
			ft_error(pipex, "error dup2(file2)", 1, id);
	}
	else
	{ 
		if (dup2(pipex->fd[1], 1) == -1)
			ft_error(pipex, "error dup2(file1)", 1, id);
	}	
}

static void	cmd_child(t_pipex *pipex, char **env, int id)
{

	switch_fd(pipex, id);
	ft_close(pipex, id);
	if (pipex->entry != -1)
		close(pipex->entry); //proteger close 
	if (pipex->o_path != NULL)
	{
		if (execve(pipex->o_path, pipex->cmd, env) == -1)
		{
			if (close(0) == -1)
				ft_error(pipex, "error close(0)", 0, id);
			if (close(1) == -1)
				ft_error(pipex, "error close(1)", 0, id);
			free(pipex->o_path);
			pipex->cmd = free_tab(pipex->cmd);
			write(2, "Command not found:\n", 19);
		}
	}
	exit(-1);
}


void	create_children(t_pipex *pipex, int ac, char **av, char **env)
{
	int		id;

	id = -1;
	while (pipex->y < (ac - 1))
	{
		if (pipe(pipex->fd) == -1)
			ft_error(pipex,"error pipe", 1, id);
		if (pipex->y == (ac - 2))
			pipex->last = 1;
		dprintf(2, "y = %d, av = %s\n", pipex->y, av[pipex->y]);
		analyse_path(pipex, av[pipex->y], env); //pas besoin de mettre o_path a null ?
		id = fork();
		if (id == -1)
		{
			ft_error(pipex,"error fork", 1, id);
		}
		if (id == 0)
			cmd_child(pipex, env, id);
		if (id != 0 && pipex->o_path != NULL)
			free(pipex->o_path);
		if (pipex->entry != -1)
			close(pipex->entry);// close l'ancien fd[0];
		pipex->entry = pipex->fd[0];
		close(pipex->fd[1]);
		pipex->y++;
	}
	ft_close(pipex, id);
}
