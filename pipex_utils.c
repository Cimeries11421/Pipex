#include "pipex.h"

void	ft_close(t_pipex *pipex, int id)
{
	if (pipex->entry != -1)
	{
		if (close(pipex->entry) == -1)
			ft_error(pipex, "error close(fd[0])", 0, id);
	}
	if (id == 0)
	{
		if (close(pipex->fd[0]) == -1)
		{
			ft_error(pipex, "error close(fd[0])", 0, id);
		}
		if (close(pipex->fd[1]) == -1)
			ft_error(pipex, "error close(fd[1])", 0, id);
	}
	if (pipex->file1 != -1)
	{	
		if (close(pipex->file1) == -1)
			ft_error(pipex, "error close(file1)", 0, id);
	}
	if (pipex->file2 != -1)
	{
		if (close(pipex->file2) == -1)
			ft_error(pipex, "error close(file2)", 0, id);
	}
}

void	ft_error(t_pipex *pipex, char *str, int close, int id)
{
	if (close == 1)
		ft_close(pipex, id);
	if (pipex->path != NULL)
	{
		dprintf(2, "boudin\n");
		pipex->path = free_tab(pipex->path);
	}
	perror(str);
	write(2, "ntm", 3);
	exit(-1);
}

size_t	strlen_space(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != ' ')
		i++;
	return (i);
}

char	*strjoin_slash(char *s1, char const *s2)
{
	char	*s3;
	size_t	len;
	size_t	i;
	char	*tmp;

	i = 0;
	len = ft_strlen(s1) + strlen_space(s2);
	s3 = malloc((len + 2) * sizeof(char)); // free 
	if (!s3)
		return (NULL);
	tmp = s1;
	while (*tmp)
		s3[i++] = *tmp++;
	s3[i] = '/';
	i++;
	while (*s2 && *s2 != ' ')
		s3[i++] = *s2++;
	s3[i] = '\0';
	free(s1);
	return (s3);
}
/*int	main(void)
{
#include <string.h>
	char *str;
	str = strdup("usr/bin");
	strjoin_slash(str, "cat   l");

	return (0);
}*/
