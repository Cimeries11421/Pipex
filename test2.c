#include<unistd.h>
#include<stdio.h>

void main(int ac, char **ar, char **env)
{
	execve("/usr/bin/cat", ar, env);
}
