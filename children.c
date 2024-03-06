/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebriere <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 18:58:24 by ebriere           #+#    #+#             */
/*   Updated: 2024/03/05 18:58:41 by ebriere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	switch_fd(t_pipex *pipex, int id)
{
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

	dprintf(2, "pipex->entry = %d\n", pipex->entry);
	switch_fd(pipex, id);
	ft_close(pipex, id);
	/*if (pipex->entry != -1)
	{
		dprintf(2, "coucou\n");
		close(pipex->entry);
			//ft_error(pipex, "error close(pipex->entry)", 0, id);
	}*/
	if (pipex->o_path != NULL)
	{
		if (execve(pipex->o_path, pipex->cmd, env) == -1)
		{
			free(pipex->o_path);
			perror("error execve");
		}
	}
	if (close(0) == -1)
		ft_error(pipex, "error close(0)", 0, id);
	if (close(1) == -1)
		ft_error(pipex, "error close(1)", 0, id);

	pipex->cmd = free_tab(pipex->cmd);
	exit(-1);
}

void	create_children(t_pipex *pipex, int ac, char **av, char **env)
{
	int		id;

	id = -1;
	while (pipex->y < (ac - 1))
	{
		if (pipe(pipex->fd) == -1)
			ft_error(pipex, "error pipe", 1, id);
		if (pipex->y == (ac - 2))
			pipex->last = 1;
		analyse_path(pipex, av[pipex->y], env);
		id = fork();
		if (id == -1)
			ft_error(pipex, "error fork", 1, id);
		if (id == 0)
			cmd_child(pipex, env, id);
		if (id != 0 && pipex->o_path != NULL)
			free(pipex->o_path);
		pipex->cmd = free_tab(pipex->cmd);
		if (pipex->entry != -1)
		{
			if (close(pipex->entry) == -1)
				ft_error(pipex, "error close(pipex->entry)", 0, id);
		}
		pipex->entry = pipex->fd[0];
		dprintf(2, "au revoir\n");
		if (close(pipex->fd[1]) == -1)
			ft_error(pipex, "error close(fd[1])", 0, id);
		pipex->y++;
	}
	ft_close(pipex, id);
}
