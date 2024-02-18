#include "pipex.h"

void	find_path(t_pipex *pipex, char **env)
{
	size_t	i;
	int	find;

	find = 0;
	i = 1;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			find = 1;
			break;
		}
		i++;
	}
	if(find == 0)
	{
		write(2, "error : PATH not found", 22);
		exit(0);
	}
	pipex->path = ft_split(env[i] + 5, ':');
	i = 0;
	while (pipex->path[i])
	{
		pipex->path[i] = strjoin_slash(pipex->path[i], pipex->arg[1]);
		printf("%s\n", pipex->path[i]);
		i++;
	}
}

void	check_path(t_pipex *pipex, char **env)
{
	size_t	i;
	(void)env;

	i = 0;
	while(pipex->path[i])
	{
		if(access(pipex->path[i], X_OK) == 0)
		{
			printf("\nline --> %s\n", pipex->path[i]);
		//	pipex->c_path = pipex->path[i];
			execve(pipex->path[i], pipex->arg, env);
			return;
		}
		i++;
	}
}


