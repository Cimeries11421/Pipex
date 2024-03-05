/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebriere <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 18:58:58 by ebriere           #+#    #+#             */
/*   Updated: 2024/03/05 18:59:00 by ebriere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static void	find_path(t_pipex *pipex, char **env)
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
		pipex->path[i] = strjoin_slash(pipex->path[i], pipex->cmd[0]);
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
			str = ft_strdup(pipex->path[i]); //secure malloc 
			pipex->path = free_tab(pipex->path);
	//		dprintf(2,"%p---\n", pipex->path);
			return (str);
		}
		i++;
	}
	pipex->path = free_tab(pipex->path);
	return (NULL); //error si trouve pas le chemin
}

/*static char		*clean_arg(char *str)
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
}*/

static char	*check(char *str)
{
	char *str2;

	str2 = ft_strdup(str);

	if (access(str2, X_OK) != 0)
	{
		dprintf(2, "false\n");
		free(str2);
		return (NULL);
	}
	dprintf(2, "str2 = %s true\n", str2);
	return (str2);
}

void	analyse_path(t_pipex *pipex, char *arg, char **env)
{
	pipex->cmd = ft_split(arg, ' '); //proteger split
//	int i = 0;
/*	while (pipex->cmd[i])
	{
		dprintf(2, "%s\n", pipex->cmd[i]);
		i++;
	}*/
	if (pipex->cmd == NULL)
	{
		write(2, "ft_split crash\n", 16);
		exit(-1);
	}
	if (!pipex->cmd[0]) //remet a null o_path si le second appel la commande = " "
		pipex->o_path = NULL;
	if (pipex->cmd[0] && ft_strchr(pipex->cmd[0], '/'))
	{
		dprintf(2, "coucou\n");
		pipex->o_path = check(pipex->cmd[0]);
	}
	else if (pipex->cmd[0])
	{
		find_path(pipex, env);
		pipex->o_path = check_path(pipex, env);
	}
	dprintf(2, "o_path = %p\n", pipex->o_path);
	dprintf(2, "o_path = %s\n", pipex->o_path);
	if(!pipex->o_path)
	{
		write(2, "Command not found: ", 19); //probleme affichage
		write(2, arg, ft_strlen(arg)); //mettre cmd[0] ??? 
		write(2, "\n", 1);
	} 
}




