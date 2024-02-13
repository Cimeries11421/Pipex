#include <stdio.h>

void	check_path(int	ac, char **av, char **env)
{
	size_t	i;

	i = 0;
	while (env[i])
	{
		printf("--> %s\n", env[i]);
		if (*env[i] == '')
		i++;
	}
}

int	main(int ac, char **av, char **env)
{
	if (ac != 5) //perror ? 
		return (-1);
	check_path(ac, av, env);
}
