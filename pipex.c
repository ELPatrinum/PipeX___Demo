/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muel-bak <muel-bak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 14:48:35 by muel-bak          #+#    #+#             */
/*   Updated: 2023/12/11 18:25:57 by muel-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	valid_cmd(char *av)
{
	if ((access(ft_strjoin("/usr/bin/", to_space(av[3])), X_OK) == 0)
		|| (access(ft_strjoin("/bin/", to_space(av[3])), X_OK) == 0) 
		|| (access(ft_strjoin("/sbin/", to_space(av[3])), X_OK) == 0)
		|| (access(ft_strjoin("/usr/sbin/", to_space(av[3])), X_OK) == 0))
	{
			return (1);
	}
	else
		return (0);
}

void	first_cmd(char **av, char **env, int *pipid)
{
	close(pipid[0]);
	dup2(pipid[1], STDOUT_FILENO);
	dup2(open(av[1], O_RDONLY, 0777), STDIN_FILENO);
	close(pipid[1]);
	if (execve("/bin/zsh", (char *[]){"zsh", "-c", av[2], NULL}, env) == -1)
	{
		perror("execve");
		exit(1);
	}
}

void	sec_cmd(char **av, char **env, int *pipid, int fd)
{
	fd = open(av[4], O_RDWR, 0777);
	if (fd >= 0)
	{
		dup2(pipid[0], STDIN_FILENO);
		dup2(fd, STDOUT_FILENO);
		close(pipid[0]);
	}
	if (fd >= 0 && (access(ft_strjoin("/usr/bin/", to_space(av[3])), X_OK) == -1)
		&& (access(ft_strjoin("/bin/", to_space(av[3])), X_OK) == -1) 
		&& (access(ft_strjoin("/sbin/", to_space(av[3])), X_OK) == -1)
		&& (access(ft_strjoin("/usr/sbin/", to_space(av[3])), X_OK) == -1))
	{
		if (execve("/bin/zsh", (char *[]){"zsh", "-c", av[3], NULL}, env) == -1)
		{
			perror("execve");
			exit(2);
		}
	}
	else if (fd < 0 && (access(ft_strjoin("/usr/bin/", to_space(av[3])), X_OK) == 0)
		|| (access(ft_strjoin("/bin/", to_space(av[3])), X_OK) == 0) 
		|| (access(ft_strjoin("/sbin/", to_space(av[3])), X_OK) == 0)
		|| (access(ft_strjoin("/usr/sbin/", to_space(av[3])), X_OK) == 0))
	{
		perror(ft_error(av[3], av[4]));
	}
	else if (fd < 0 && (access(ft_strjoin("/usr/bin/", to_space(av[3])), X_OK) == -1)
		&& (access(ft_strjoin("/bin/", to_space(av[3])), X_OK) == -1) 
		&& (access(ft_strjoin("/sbin/", to_space(av[3])), X_OK) == -1)
		&& (access(ft_strjoin("/usr/sbin/", to_space(av[3])), X_OK) == -1))
	{
		if (execve("/bin/zsh", (char *[]){"zsh", "-c", av[3], NULL}, env) == -1)
		{
			perror("execve");
			exit(2);
		}
	}
	else if (fd >= 0 && (access(ft_strjoin("/usr/bin/", to_space(av[3])), X_OK) == 0)
		|| (access(ft_strjoin("/bin/", to_space(av[3])), X_OK) == 0) 
		|| (access(ft_strjoin("/sbin/", to_space(av[3])), X_OK) == 0)
		|| (access(ft_strjoin("/usr/sbin/", to_space(av[3])), X_OK) == 0))
	{
		if (execve("/bin/zsh", (char *[]){"zsh", "-c", av[3], NULL}, env) == -1)
		{
			perror("execve");
			exit(2);
		}
	}
}

int	pipex(char **av, char **env)
{
	pid_t	pid1;
	pid_t	pid2;
	int		pipid[2];
	int		fd;

	if (pipe(pipid) == -1)
		return (1);
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
