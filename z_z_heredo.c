/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_z_heredo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muel-bak <muel-bak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 18:04:18 by muel-bak          #+#    #+#             */
/*   Updated: 2023/12/13 20:42:39 by muel-bak         ###   ########.fr       */
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
// void	here_doc1()
// {
// }

// void	ft_here_doc(char **av, char **env)
// {
// 	pid_t	pid1;
// 	pid_t	pid2;
// 	int		pipid[2];
// 	int		fd;

// 	fd = 0;
// 	if (pipe(pipid) == -1)
// 		return (1);
// 	pid1 = fork();
// 	if (pid1 == -1)
// 		return (2);
// 	if (pid1 == 0)
// 		first_cmd(av, env, pipid, fd);
// 	close(pipid[1]);
// 	pid2 = fork();
// 	if (pid2 == -1)
// 		return (3);
// 	if (pid2 == 0)
// 		sec_cmd(av, env, pipid, fd);
// 	close(pipid[0]);
// 	waitpid(pid1, NULL, 0);
// 	waitpid(pid2, NULL, 0);
// 	return (0);
// }