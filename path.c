#include "pipex.h"

char	**free_tab(char **tab)
{
	size_t	i;

	i = 0;

//	dprintf(2,"%s\n", **tab);
	while (tab[i])
	{
		//dprintf(2, "tab[%ld] = %s\n", i , (*tab)[i]);
		free(tab[i]);
		i++;
	}
	free(tab);
	tab = NULL;
	return (tab);
//	dprintf(2,"%p\n", pipex->path);
}

static void	find_path(t_pipex *pipex, char **env, char *cmd)
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
	if (find == 0)
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

static char	*check_path(t_pipex *pipex, char **env)
{
	size_t	i;
	char	*str;
	(void)env; // a retirer

	i = 0;
	while (pipex->path[i])
	{
		if (access(pipex->path[i], X_OK) == 0)
		{
			str = ft_strdup(pipex->path[i]);
			pipex->path = free_tab(pipex->path);
	//		dprintf(2,"%p---\n", pipex->path);
			return (str);
		}
		i++;
	}
	return (NULL); //error si trouve pas le chemin
}

static char		*clean_arg(char *str)
{
	size_t	i;
	char	*str2;
	
	//dprintf(2, "arg = %s\n", str);
	i = 0;
	while (str[i] != ' ')
		i++;
	str2 = malloc((i + 1) * sizeof(char));
	i = 0;
	while (str[i] != ' ')
	{
		str2[i] = str[i];
		i++;
	}
	str2[i] = '\0';	
	//dprintf(2, "str2 = %s\n", str2);
	if (access(str2, X_OK) != 0)
	{
		free(str2);
		return (NULL);
	}
	return (str2);
}

void	analyse_path(t_pipex *pipex, char *arg, char **env)
{
	if (ft_strchr(arg, '/'))
	{
		dprintf(2, "coucou\n");
		pipex->o_path = clean_arg(arg);
	}
	else
	{	
		find_path(pipex, env, arg);
		pipex->o_path = check_path(pipex, env);
	}
	dprintf(2, "o_path = %p\n", pipex->o_path);
	if (!pipex->o_path)
	{
		write(2, "Command not found: ", 19); //probleme affichage
		write(2, arg, ft_strlen(arg));
		write(2, "\n", 1);
	} 
}






