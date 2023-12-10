#include "pipex.h"

int pipex(char **av, char **env)
{
    pid_t pid1;
	pid_t	pid2;
    int pipid[2];
	int fd;

    if (pipe(pipid) == -1)
	{
        perror("pipe");
        return 1;
    }
    pid1 = fork();
    if (pid1 == -1)
	{
        perror("fork");
        return 2;
    }
    if (pid1 == 0)
	{
        close(pipid[0]);
        dup2(pipid[1], STDOUT_FILENO);
		dup2(open(av[1], O_RDONLY, 0777), STDIN_FILENO);
        close(pipid[1]);
        if (execve("/bin/sh", (char *[]){"sh", "-c", av[2], NULL}, env) == -1)
		{
            perror("execve");
            exit(1);
        }
    }
    close(pipid[1]);
    pid2 = fork();
    if (pid2 == -1)
	{
        perror("fork");
        return 3;
    }
    if (pid2 == 0)
	{
        if ((fd = open(av[4], O_RDWR, 0777)) == -1)
			perror("open c2");
		dup2(pipid[0], STDIN_FILENO);
		dup2(fd, STDOUT_FILENO);
        if (execve("/bin/sh", (char *[]){"sh", "-c", av[3], NULL}, env) == -1)
		{
            perror("execve");
            exit(2);
        }
    }
    close(pipid[0]);

    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return 0;
}

int main(int ac, char **av, char **env)
{
    return pipex(av, env);
}
