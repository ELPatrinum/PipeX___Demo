/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muel-bak <muel-bak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 15:31:38 by muel-bak          #+#    #+#             */
/*   Updated: 2023/12/10 16:40:04 by muel-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int pipex(char **av, char **env)
{
	int pid;
	int pipid[2];
	int fd;
	int dupfd;
	if (pipe(pipid) == -1)
		return (1);
	pid = fork();
	if (pid == 0)
	{
		if((fd = open(av[1], O_WRONLY, 0777)) == -1)
			perror("open C");
		dupfd = dup2(fd, STDOUT_FILENO);
		if (execve(to_space(av[2]), ft_split(av[2],  ' '), env) == -1)
			perror("execve C");
	}
	else
	{
		// if ((fd = open(av[4], O_RDONLY, 0777)) == -1)
		// 	perror("open P");
		// dupfd  = dup2(fd, 1);
		// if (execve(to_space(av[3]), ft_split(av[3], ' '), env) == -1)
		// 	perror("execve P");
	}
   return 0;
}

int main(int ac, char **av, char **env)
{

	//printf("%s:%s", to_space(av[2]), to_space(av[3]));
	return (pipex(av, env));
}

// $> ./pipex infile "ls -l" "wc -l" outfile