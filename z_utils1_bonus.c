/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_utils1_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muel-bak <muel-bak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:33:29 by muel-bak          #+#    #+#             */
/*   Updated: 2023/12/13 20:42:17 by muel-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "z_pipex_bonus.h"

void	first_cmd(char **av, char **env, int *pipid, int fd)
{
	char	*line;

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
		perror(line = ft_error(av[2], av[1]));
	else if (fd < 0 && !valid_cmd(av[2]))
		perror(ft_error(av[2], av[1]));
	else if (fd >= 0 && valid_cmd(av[2]))
	{
		if (execve("/bin/sh", (char *[]){"sh", "-c", av[2], NULL}, env) == -1)
			exit(2);
	}
}

void	sec_cmd(char **av, char **env, int fd, int last)
{
	fd = open(av[last + 1], O_RDWR, 0777);
	if (fd >= 0)
	{
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	if (fd >= 0 && !valid_cmd(av[last]))
	{
		if (execve("/bin/sh", (char *[]){"sh", "-c", av[last], NULL}, env) > 0)
			exit(2);
	}
	else if (fd < 0 && valid_cmd(av[last]))
	{
		perror(ft_error(av[last], av[last + 1]));
	}
	else if (fd < 0 && !valid_cmd(av[last]) && write(2, "-", 1))
	{
		if (execve("/bin/sh", (char *[]){"sh", "-c", av[last], NULL}, env) > 0)
			exit(2);
	}
	else if (fd >= 0 && valid_cmd(av[last]))
	{
		if (execve("/bin/sh", (char *[]){"sh", "-c", av[last], NULL}, env) > 0)
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

int	valid_cmd(char *av)
{
	if ((access(ft_strjoin("/usr/bin/", to_space(av)), X_OK) == 0)
		|| (access(ft_strjoin("/bin/", to_space(av)), X_OK) == 0)
		|| (access(ft_strjoin("/sbin/", to_space(av)), X_OK) == 0)
		|| (access(ft_strjoin("/usr/sbin/", to_space(av)), X_OK) == 0)
		|| (access(ft_strjoin("/usr/local/bin/", to_space(av)), X_OK) == 0)
		|| (access(ft_strjoin("/usr/local/munki/", to_space(av)), X_OK) == 0))
	{
		return (1);
	}
	else
		return (0);
}
