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
		exit(-1);
	}
	pipex->path = ft_split(env[i] + 5, ':');
	i = 0;
	while (pipex->path[i])
	{
		pipex->path[i] = strjoin_slash(pipex->path[i], cmd);
	//	dprintf(2,"%s\n", pipex->path[i]);
		i++;
	}
}

void	free_tab(char ***tab)
{
	size_t	i;

	i = 0;

//	dprintf(2,"%s\n", **tab);
	while ((*tab)[i])
	{
		//dprintf(2, "tab[%ld] = %s\n", i , (*tab)[i]);
		free(*tab[i]);
		i++;
	}
	free(*tab);
	*tab = NULL;
//	dprintf(2,"%p\n", pipex->path);
}

char	*check_path(t_pipex *pipex, char **env)
{
	size_t	i;
	char	*str;
	(void)env;

	i = 0;
	while (pipex->path[i])
	{
		if (access(pipex->path[i], X_OK) == 0)
		{
	//		printf("\nline --> %s\n", pipex->path[i]);
			str = ft_strdup(pipex->path[i]);
			free_tab(&pipex->path);
			dprintf(2,"%p---\n", pipex->path);
			return (str);
		}
		i++;
	}
	return (NULL); //error si trouve pas le chemin
}


