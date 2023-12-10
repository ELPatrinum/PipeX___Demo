/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muel-bak <muel-bak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 15:31:38 by muel-bak          #+#    #+#             */
/*   Updated: 2023/12/10 16:57:13 by muel-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int pipex(char **av, char **env)
{
	pid_t pid;
	pid_t pid2;
	int pipid[2];
	int fd;
	int dupfd1;
	int dupfd2;
	if (pipe(pipid) == -1)
		return (1);
	pid = fork();
	if (pid == 0)
	{
		if((fd = open(av[1], O_WRONLY, 0777)) == -1)
			perror("open c1");
		dupfd1 = dup2(fd, STDOUT_FILENO);
		dupfd2 = dup2(pipid[1], dupfd1);
		if (execve(to_space(av[2]), ft_split(av[2],  ' '), env) == -1)
			perror("execve c1");
	}
	pid2 = fork();
	if (pid2 == 0)
	{
		if ((fd = open(av[4], O_RDONLY, 0777)) == -1)
			perror("open c2");
		dupfd1 = dup2(fd, STDIN_FILENO);
		dupfd2 = dup2(pipid[0], dupfd1);
		if (execve(to_space(av[3]), ft_split(av[3], ' '), env) == -1)
			perror("execve c2");		
	}
	waitpid(pid, NULL, 0);
	waitpid(pid2, NULL, 0);
   return 0;
}

int main(int ac, char **av, char **env)
{

	//printf("%s:%s", to_space(av[2]), to_space(av[3]));
	return (pipex(av, env));
}

// $> ./pipex infile "ls -l" "wc -l" outfile