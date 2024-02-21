#include "pipex.h"
#include <stdio.h>

void	cmd_child(t_pipex *pipex, char **av, char **env, int *fd)
{
	int	new_fd;
	int		p_cmd;
	char	**cmd;

	new_fd = -1;//dup2(fd[1], 1); // 1 pour l'ecriture
	if(new_fd == -1)
	{
		fd = NULL;
		//message
		write(2, strerror(errno), ft_strlen(strerror(erno)));
		exit(-1);
	}
	if(close(fd[0]) == -1)
	{
		//message
		exit(-1);
	}
	if(close(fd[1]) == -1)
	{
		//message
		exit(-1);
	}
	find_path(pipex, env);
	p_cmd = check_path;
	cmd = ft_split(av);
	if(execve(env[p_cmd], cmd, env) == -1)
	{
		//message
		exit(-1);
	}
}

int main(int ac, char **av, char **env)
{
	int		fd[2];
	int		id;
	t_pipex	pipex;
	
	pipex->c_arg = ac;
	if (pipe(fd) == -1)
	{
		//
		return(-1);
	}
	id = fork();
	if (id == 0)
		cmd_child(&pipex, av, env, fd);
	return (0);
}
