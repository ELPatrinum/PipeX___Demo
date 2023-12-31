/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muel-bak <muel-bak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:33:29 by muel-bak          #+#    #+#             */
/*   Updated: 2023/12/13 23:34:56 by muel-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_cmd(char **av, char **env, int *pipid, int fd)
{
	fd = open(av[1], O_RDONLY, 0777);
	if (fd >= 0)
	{
		close(pipid[0]);
		dup2(pipid[1], STDOUT_FILENO);
		dup2(fd, STDIN_FILENO);
		close(pipid[1]);
	}
	if (fd >= 0 && !valid_cmd(av[2]))
	{
		write(2, "-", 1);
		if (execve("/bin/sh", (char *[]){"sh", "-c", av[2], NULL}, env) == -1)
			exit(2);
	}
	else if (fd < 0 && valid_cmd(av[2]))
		perror(ft_error(av[2], av[1]));
	else if (fd < 0 && !valid_cmd(av[2]))
		perror(ft_error(av[2], av[1]));
	else if (fd >= 0 && valid_cmd(av[2]))
	{
		if (execve("/bin/sh", (char *[]){"sh", "-c", av[2], NULL}, env) == -1)
			exit(2);
	}
}

void	sec_cmd(char **av, char **env, int *pipid, int fd)
{
	fd = open(av[4], O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fd >= 0)
	{
		dup2(pipid[0], STDIN_FILENO);
		dup2(fd, STDOUT_FILENO);
		close(pipid[0]);
	}
	if (fd >= 0 && !valid_cmd(av[3]))
	{
		write(2, "-", 1);
		if (execve("/bin/sh", (char *[]){"sh", "-c", av[3], NULL}, env) == -1)
			exit(2);
	}
	else if (fd < 0 && valid_cmd(av[3]))
		perror(ft_error(av[3], av[4]));
	else if (fd < 0 && !valid_cmd(av[3]) && write(2, "-", 1))
	{
		if (execve("/bin/sh", (char *[]){"sh", "-c", av[3], NULL}, env) == -1)
			exit(2);
	}
	else if (fd >= 0 && valid_cmd(av[3]))
	{
		if (execve("/bin/sh", (char *[]){"sh", "-c", av[3], NULL}, env) == -1)
			exit(2);
	}
}

int	spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] == ' ')
		i++;
	return (i);
}

void	ft_puterror(char *str)
{
	if (*str)
	{
		write(2, str, 1);
		ft_puterror(str + 1);
	}
}
