#include "pipex.h"

void	ft_error(t_pipex *pipex, char *str)
{
	if (pipex->path != NULL)
	{
		dprintf(2,"boudin\n");
		free_tab(&pipex->path);
	}
	 perror(str);
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
