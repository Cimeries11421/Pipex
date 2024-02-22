#include "pipex.h"

void	find_path(t_pipex *pipex, char **env, char *cmd)
{
	size_t	i;
	int		find;

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
		pipex->path[i] = strjoin_slash(pipex->path[i], cmd);
	//	printf("%s\n", pipex->path[i]);
		i++;
	}
}

int	check_path(t_pipex *pipex, char **env)
{
	size_t	i;
	(void)env;

	i = 0;
	while (pipex->path[i])
	{
		if (access(pipex->path[i], X_OK) == 0)
		{
	//		printf("\nline --> %s\n", pipex->path[i]);
			return (i);
		}
		i++;
	}
	return (-1); //error si trouve pas le chemin
}


