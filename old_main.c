#include "pipex.h"
#include <stdio.h>

/*void	first_fork(t_pipex *pipex, int *fd)
{
	dup2(pipex->file1, 0)
	dup2(fd[1], 1);
	close(fd[0]);
	close(fd[1]);
	close(pipex->file1);
}

void	next_fork(t_pipex *pipex, int *fd)
{
	dup2(fd[0], 0);
	dup2(fd[1], 1);
	close(fd[0]);
	close(fd[1]);
}*/


void	cmd_child(t_pipex *pipex, char *arg, char **env, int *fd)
{
	int		p_cmd;
	char	**cmd;

	printf("entry = %d\n", pipex->entry);
	if (pipex->entry == -1)
	{

		printf("1er fork\n\n");
		dup2(pipex->file1, 0);
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		close(pipex->file1);
	}
	else if (pipex->entry != -1 && pipex->last == 0)
	{
	//	printf("last = %d\n", pipex->last);
		printf("2 eme fork\n\n");
		dup2(pipex->entry, 0);
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);

	}
	if (pipex->last == 1)
	{
		printf("dernier fork\n\n");
		dup2(pipex->entry, 0);
		dup2(pipex->file2, 1);
		close(pipex->file2);
		close(pipex->entry);
		close(fd[0]);
		close(fd[1]);
	}
	find_path(pipex, env, arg);
	p_cmd = check_path(pipex, env);
	cmd = ft_split(arg, ' ');
	if (execve(pipex->path[p_cmd], cmd, env) == -1)
	{
		//free
		//message
		exit(-1);
	}
	exit(0);
}

int main(int ac, char **av, char **env)
{
	int		fd[2];
	int		id;
	t_pipex	pipex;
	int		y;

    printf("%s", av[ac]);
	pipex.file1 = open(av[1], O_RDONLY, 0666); // permission a revoir
	pipex.file2 = open(av[ac - 1], O_WRONLY /*| O_CREAT*/ | O_TRUNC, 0666);
	pipex.entry = -1;
	y = 2;
	pipex.last = 0;
	while (y <= ac - 2)
	{
		pipe(fd);
		id = fork();
		if(y == ac - 2)
		{
			pipex.last = 1;
		}
		if (id == 0)
		{
			printf("y = %d av[y] = %s\n", y, av[y]);
			cmd_child(&pipex, av[y], env, fd);
		}
		pipex.entry = fd[0]; // prends l'entree de l'ancien pipe
		printf("entry2 = %d\n", pipex.entry);
		
//		close(fd[0]); pas close 
		close(fd[1]);
		y++;
		//i++;
	}
//	wait();
//	dup2(fd[])
	return (0);
}


/*	if(new_fd == -1) //a mettre sur une ligne avec celle du dessus.
	{
		fd = NULL;
		//message
		//write(2, strerror(errno), ft_strlen(strerror(errno)));
		exit(-1);
	}
*/
