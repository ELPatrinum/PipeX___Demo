/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muel-bak <muel-bak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 14:48:35 by muel-bak          #+#    #+#             */
/*   Updated: 2023/12/11 15:03:34 by muel-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

void	first_cmd(char **av, char **env, int *pipid)
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

void	sec_cmd(char **av, char **env, int *pipid, int fd)
{
	fd = open(av[4], O_RDWR, 0777);
	if (fd == -1)
	{
		perror("open");
		exit(1);
	}
	dup2(pipid[0], STDIN_FILENO);
	dup2(fd, STDOUT_FILENO);
	close(pipid[0]);
	if (execve("/bin/zsh", (char *[]){"zsh", "-c", av[3], NULL}, env) == -1)
	{
		perror("execve");
		exit(2);
	}
}

int	pipex(char **av, char **env)
{
	pid_t	pid1;
	pid_t	pid2;
	int		pipid[2];
	int		fd;

	if (pipe(pipid) == -1)
	{
		perror("pipe");
		return (1);
	}
	pid1 = fork();
	if (pid1 == -1)
		return (2);
	if (pid1 == 0)
		first_cmd(av, env, pipid);
	close(pipid[1]);
	pid2 = fork();
	if (pid2 == -1)
		return (3);
	if (pid2 == 0)
		sec_cmd(av, env, pipid, fd);
	close(pipid[0]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	return (pipex(av, env));
}
