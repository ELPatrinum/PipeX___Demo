/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muel-bak <muel-bak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:33:29 by muel-bak          #+#    #+#             */
/*   Updated: 2023/12/11 19:18:49 by muel-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	valid_cmd(char *av)
{
	if ((access(ft_strjoin("/usr/bin/", to_space(av)), X_OK) == 0)
		|| (access(ft_strjoin("/bin/", to_space(av)), X_OK) == 0) 
		|| (access(ft_strjoin("/sbin/", to_space(av)), X_OK) == 0)
		|| (access(ft_strjoin("/usr/sbin/", to_space(av)), X_OK) == 0))
	{
		return (1);
	}
	else
		return (0);
}

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
		if (execve("/bin/zsh", (char *[]){"zsh", "-c", av[2], NULL}, env) == -1)
			exit(2);
	}
	else if (fd < 0 && valid_cmd(av[2]))
		perror(ft_error(av[2], av[1]));
	else if (fd < 0 && !valid_cmd(av[2]))
		perror(ft_error(av[2], av[1]));
	else if (fd >= 0 && valid_cmd(av[2]))
	{
		if (execve("/bin/zsh", (char *[]){"zsh", "-c", av[2], NULL}, env) == -1)
			exit(2);
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
	if (fd >= 0 && !valid_cmd(av[3]))
	{
		if (execve("/bin/zsh", (char *[]){"zsh", "-c", av[3], NULL}, env) == -1)
			exit(2);
	}
	else if (fd < 0 && valid_cmd(av[3]))
		perror(ft_error(av[3], av[4]));
	else if (fd < 0 && !valid_cmd(av[3]))
	{
		if (execve("/bin/zsh", (char *[]){"zsh", "-c", av[3], NULL}, env) == -1)
			exit(2);
	}
	else if (fd >= 0 && valid_cmd(av[3]))
	{
		if (execve("/bin/zsh", (char *[]){"zsh", "-c", av[3], NULL}, env) == -1)
			exit(2);
	}
}
