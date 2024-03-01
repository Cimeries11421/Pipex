#include "pipex.h"

/*void	first_child(t_pipex *pipex)
{
	if (close(pipex->file1) == -1)
		ft_error("error close(file1)");
}*/

static char		*clean_arg(char *str)
{
	size_t	i;
	char	*str2;
	
	dprintf(2, "arg = %s\n", str);
	i = 0;
	while (str[i] != ' ')
		i++;
	str2 = malloc(i * sizeof(char));
	i = 0;
	while (str[i] != ' ')
	{
		str2[i] = str[i];
		i++;
	}
	str2[i] = '\0';	
	dprintf(2, "str2 = %s\n", str2);
	if (access(str2, X_OK) != 0)
	{
		free(str2);
		return (NULL);
	}
	return (str2);
}

static void	switch_fd(t_pipex *pipex)
{
	if (pipex->entry == -1)
	{
		if (dup2(pipex->file1, 0) == -1)
			ft_error(pipex, "error dup2(file1)", 1);
	}
	else if (pipex->entry != -1)
	{
		if (dup2(pipex->entry, 0) == -1)
			ft_error(pipex, "error dup2(entry)", 1);
	}
	if (pipex->last == 1)
	{
		if (dup2(pipex->file2, 1) == -1)
			ft_error(pipex, "error dup2(file2)", 1);
	}
	else
	{ 
		if (dup2(pipex->fd[1], 1) == -1)
			ft_error(pipex, "error dup2(file1)", 1);
	}	
}

static void	cmd_child(t_pipex *pipex, char *arg, char **env)
{
	char	*o_path;
	char	**cmd;

	cmd = NULL; // ?
	switch_fd(pipex);
	ft_close(pipex);
	if (pipex->entry != -1)
		close(pipex->entry);
	if (ft_strchr(arg, '/'))
	{
		dprintf(2, "coucou\n");
		o_path = clean_arg(arg);
	}
	else
	{	
		find_path(pipex, env, arg);
		o_path = check_path(pipex, env);
	}
	dprintf(2, "o_path = %p\n", o_path);
	if (!o_path)
	{
		write(2, "Command not found: ", 18); //probleme affichage
		write(2, arg, ft_strlen(arg));
		write(2, "\n", 1);
		return ;
	}
	dprintf(2, "av = %s\n", arg);
	cmd = ft_split(arg, ' ');
	if (execve(o_path, cmd, env) == -1)
	{
		//close 0 et 1 et 
		//if(close(pipex->entry) == -1)
		//	ft_error(pipex, "error close(file2)");
		free(o_path);
		cmd = free_tab(cmd);
		ft_error(pipex,"error execve", 1);
	}
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
		id = fork();
		if (id == -1)
		{
			ft_error(pipex,"error fork", 1);
		}
		if (y == (ac - 2))
			pipex->last = 1;
		if (id == 0)
			cmd_child(pipex, av[y], env);
		if (pipex->entry != -1)
			close(pipex->entry);// close l'ancien fd[0];
		pipex->entry = pipex->fd[0];
		close(pipex->fd[1]);
		y++;
	}
}
