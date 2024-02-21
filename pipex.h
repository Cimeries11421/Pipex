#ifndef PIPEX_H
# define PIPEX_H

#include "libft.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

typedef struct	s_pipex
{
	int		c_arg;
	char	**arg;
	char	**path;
	char	**cmd_path;
}			t_pipex;

char	*strjoin_slash(char *s1, char const *s2);
size_t	strlen_space(const char *str);
void	find_path(t_pipex *pipex, char **env);
int		check_path(t_pipex *pipex, char **env);

#endif
