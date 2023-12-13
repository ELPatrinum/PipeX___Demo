/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_z_heredo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muel-bak <muel-bak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 18:04:18 by muel-bak          #+#    #+#             */
/*   Updated: 2023/12/14 00:12:45 by muel-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "z_pipex_bonus.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t	i;

	i = 0;
	while (str1[i] && str2[i] && str1[i] == str2[i] && i < n - 1)
		i++;
	if (i == n)
		return (0);
	return ((unsigned char)str1[i] - (unsigned char)str2[i]);
}

void	here_first_cmd(char **av, char **env, int *pipid)
{
	close(pipid[0]);
	dup2(pipid[1], STDOUT_FILENO);
	close(pipid[1]);
	if (!valid_cmd(av[3]))
	{
		write(2, "-", 1);
		if (execve("/bin/sh", (char *[]){"sh", "-c", av[3], NULL}, env) == -1)
			exit(2);
	}
	else
	{
		if (execve("/bin/sh", (char *[]){"sh", "-c", av[3], NULL}, env) == -1)
			exit(2);
	}
}

void	here_sec_cmd(char **av, char **env, int *pipid, int fd)
{
	fd = open(av[5], O_RDWR | O_APPEND, 0777);
	if (fd >= 0)
	{
		dup2(pipid[0], STDIN_FILENO);
		dup2(fd, STDOUT_FILENO);
		close(pipid[0]);
	}
	if (fd >= 0 && !valid_cmd(av[5]))
	{
		write(2, "-", 1);
		if (execve("/bin/sh", (char *[]){"sh", "-c", av[4], NULL}, env) == -1)
			exit(2);
	}
	else if (fd < 0 && valid_cmd(av[4]))
		perror(ft_error(av[5], av[4]));
	else if (fd < 0 && !valid_cmd(av[4]) && write(2, "-", 1))
	{
		if (execve("/bin/sh", (char *[]){"sh", "-c", av[5], NULL}, env) == -1)
			exit(2);
	}
	else if (fd >= 0 && valid_cmd(av[4]))
	{
		if (execve("/bin/sh", (char *[]){"sh", "-c", av[4], NULL}, env) == -1)
			exit(2);
	}
}

int	here_doc_pipex(char **av, char **env)
{
	pid_t	pid1;
	pid_t	pid2;
	int		pipid[2];
	int		fd;

	fd = 0;
	if (pipe(pipid) == -1)
		return (1);
	pid1 = fork();
	if (pid1 == -1)
		return (2);
	if (pid1 == 0)
		here_first_cmd(av, env, pipid);
	close(pipid[1]);
	pid2 = fork();
	if (pid2 == -1)
		return (3);
	if (pid2 == 0)
		here_sec_cmd(av, env, pipid, fd);
	close(pipid[0]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}

int	ft_here_doc(int ac, char **av, char **env)
{
	(void)ac;
	if (ft_strlen(av[3]) == 0 || ft_strlen(av[4]) == 0)
		return (ft_puterror("-sh: : command not found\n"), 0);
	if (ft_strlen(av[4]) == spaces(av[4]))
	{
		ft_puterror("-sh: ");
		ft_puterror(av[4]);
		ft_puterror(": command not found\n");
		return (0);
	}
	else if (ft_strlen(av[4]) == spaces(av[4]))
	{
		ft_puterror("-sh: ");
		ft_puterror(av[4]);
		ft_puterror(": command not found\n");
		return (0);
	}
	else
		return (here_doc_pipex(av, env));
}
