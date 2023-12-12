/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muel-bak <muel-bak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 14:48:35 by muel-bak          #+#    #+#             */
/*   Updated: 2023/12/12 17:39:22 by muel-bak         ###   ########.fr       */
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

void	empty_or_space_error(char **av, char **env, int args)
{
	if (ft_strlen(av[2]) == 0 || ft_strlen(av[3]) == 0)
	{
		ft_puterror("-sh: : command not found\n");
		exit (0);
	}
	if (ft_strlen(av[2]) == spaces(av[2]))
	{
		ft_puterror("-sh: ");
		ft_puterror(av[2]);
		ft_puterror(": command not found\n");
		exit (0);
	}
	else if (ft_strlen(av[3]) == spaces(av[3]))
	{
		ft_puterror("-sh: ");
		ft_puterror(av[3]);
		ft_puterror(": command not found\n");
		exit (0);
	}
	else
		pipex(av, env, args);
}
void	mid_cmd_run(char **av, char **env, int *pipid, int arg)
{
	dup2(pipid[1], STDOUT_FILENO);
	close(pipid[1]);
	close(pipid[0]);
	if (!valid_cmd(av[3]))
	{
		write(2, "-", 1);
		execve("/bin/sh", (char *[]){"sh", "-c", av[arg], NULL}, env);
			exit(2);
	}
	else
	{
		if (execve("/bin/sh", (char *[]){"sh", "-c", av[arg], NULL}, env) == -1)
			exit (1);
	}
}
void mid_cmd(char **av, char **env, int args)
{
	int		arg;
	pid_t	pid1;
	int		pipid[2];

	arg = 3;
	while (arg < args)
	{
		if (pipe(pipid) == -1)
			exit (1);
		pid1 = fork();
		if (pid1 == -1)
			exit (2);
		if (pid1 == 0)
		{
			mid_cmd_run(av, env, pipid, arg);
		}
		else
		{
			waitpid(pid1, NULL, 0);
			close(pipid[1]);
			dup2(pipid[0], STDIN_FILENO);
			close(pipid[0]);
			arg++;
		}
	}
}

int	pipex(char **av, char **env, int args)
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
	dup2(pipid[0], STDIN_FILENO);
	close(pipid[0]);
	mid_cmd(av, env, args);
	pid2 = fork();
	if (pid2 == -1)
		return (3);
	if (pid2 == 0)
		sec_cmd(av, env, fd, args);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	int args;

	args = ac - 2;
	empty_or_space_error(av, env, args);
}
//./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2