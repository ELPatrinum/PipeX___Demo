/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muel-bak <muel-bak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 14:48:35 by muel-bak          #+#    #+#             */
/*   Updated: 2023/12/12 13:00:27 by muel-bak         ###   ########.fr       */
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

int	pipex(char **av, char **env)
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
		first_cmd(av, env, pipid, fd);
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
	(void)ac;
	if (ft_strlen(av[2]) == 0 || ft_strlen(av[3]) == 0)
	{
		ft_puterror("-sh: : command not found\n");
		return (0);
	}
	if (ft_strlen(av[2]) == spaces(av[2]))
	{
		ft_puterror("-sh: ");
		ft_puterror(av[2]);
		ft_puterror(": command not found\n");
		return (0);
	}
	else if (ft_strlen(av[3]) == spaces(av[3]))
	{
		ft_puterror("-sh: ");
		ft_puterror(av[3]);
		ft_puterror(": command not found\n");
		return (0);
	}
	else
		return (pipex(av, env));
}
