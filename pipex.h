#ifndef PIPEX_H
# define PIPEX_H

#include "libft.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>

typedef struct	s_pipex
{
	int		file1;
	int		file2;
	int		fd[2];
	int		entry;
	int		last;
	char	**path;
	char	*o_path;

}			t_pipex;

char	*strjoin_slash(char *s1, char const *s2);
size_t	strlen_space(const char *str);
void	ft_error(t_pipex *pipex, char *str, int close);
char	**free_tab(char **tab);
void	ft_close(t_pipex *pipex);
void	create_children(t_pipex *pipex, int ac, char **av, char **env);
void	analyse_path(t_pipex *pipex, char *arg, char **env);

#endif
