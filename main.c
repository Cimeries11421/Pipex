#include "pipex.h"
#include <stdio.h>

void	cmd_child(t_pipex *pipex, char *arg, char **env, int *fd)
{
	int		p_cmd;
	char	**cmd;
	int		new_fd;

	if (dup2(pipex->file1, 0) == -1)
	{
		//message
		exit(-1);
	}
	new_fd = dup2(fd[1], 1);
	if(new_fd == -1) //a mettre sur une ligne avec celle du dessus.
	{
		fd = NULL;
		//message
		//write(2, strerror(errno), ft_strlen(strerror(errno)));
		exit(-1);
	}
	if (close(fd[0]) == -1)
	{
		//message
		exit(-1);
	}

	if (close(fd[1]) == -1)
	{
		printf("exit");
		exit(-1);
	}
	find_path(pipex, env, arg);
	p_cmd = check_path(pipex, env);
	cmd = ft_split(arg, ' ');
	int i = 0;
	while (cmd[i])
	{
		printf("-->%s\n", cmd[i]);
		i++;
	}
	if (execve(pipex->path[p_cmd], cmd, env) == -1)
	{
		//free
		//message
		exit(-1);
	}
}

void	process(t_pipex *pipex, char *arg, char **env, int *fd)
{
	int		p_cmd;
	char	**cmd;

	if (dup2(fd[0], 0) == -1)
	{
		//message
		exit(-1);
	}
	if (dup2(pipex->file2, 1) == -1)
	{
		//message
		exit(-1);
	}
	if (close(fd[0]) == -1)
	{
		exit(-1);	
	}
	find_path(pipex, env, arg);
	p_cmd = check_path(pipex, env);
	cmd = ft_split(arg, ' ');
	if (execve(pipex->path[p_cmd], cmd, env) == -1)
	{
		//free
		//message
		exit(-1);
	}
}

int main(int ac, char **av, char **env)
{
	int		fd[2];
	int		id;
	t_pipex	pipex;

	pipex.file1 = open(av[1], O_RDONLY, 0666); // permission a revoir
	pipex.file2 = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	printf("pipex.file2 = %d\n",pipex.file2 );
	pipex.c_arg = ac;
	if (pipe(fd) == -1)
	{
		//
		return (-1);
	}
	id = fork();
	if (id == 0)
		cmd_child(&pipex, av[2], env, fd);
	else
		process(&pipex, av[3], env, fd);
	return (0);
}
