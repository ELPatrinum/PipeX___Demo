/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_z_herdoc2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muel-bak <muel-bak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 12:06:31 by muel-bak          #+#    #+#             */
/*   Updated: 2023/12/14 00:11:58 by muel-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "z_pipex_bonus.h"

char	*read_from_fd(int fd, char *remains)
{
	char		*buff;
	long long	size;

	size = 1;
	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (free(remains), NULL);
	while (size > 0 && !new_line_check(remains))
	{
		size = read(fd, buff, BUFFER_SIZE);
		if (size == 0)
			break ;
		if (size == -1)
		{
			free(buff);
			free(remains);
			return (NULL);
		}
		buff[size] = '\0';
		remains = ft_strjoin_b(remains, buff);
	}
	free(buff);
	return (remains);
}

char	*get_theline(char *str)
{
	int		i;
	char	*line;

	if (!*str)
		return (NULL);
	line = malloc((ft_strlen_pro(str, 0, '\n') + 1) * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*update_remains(char *remains)
{
	char	*new_remains;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!remains)
		return (free(remains), NULL);
	while (remains[i] != '\0' && remains[i] != '\n')
		i++;
	if (!remains[i])
	{
		free(remains);
		return (NULL);
	}
	new_remains = malloc((ft_strlen_pro(remains, i, '\0')) * sizeof(char));
	if (!new_remains)
		return (free(remains), NULL);
	i++;
	while (remains[i])
		new_remains[j++] = remains[i++];
	new_remains[j] = '\0';
	free(remains);
	return (new_remains);
}

char	*get_next_line(int fd)
{
	static char	*remains;
	char		*theline;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	remains = read_from_fd(fd, remains);
	if (!remains)
		return (NULL);
	theline = get_theline(remains);
	if (!theline)
	{
		free(remains);
		remains = NULL;
		return (NULL);
	}
	remains = update_remains(remains);
	return (theline);
}

void	run_here_doc(int ac, char **av, char **env, t_ptr ptr)
{
	ptr.limiter = ft_strjoin(av[2], "\n");
	while (1)
	{
		write(1, "here_doc> ", 11);
		ptr.line = get_next_line(0);
		if (!ft_strncmp(ptr.line, ptr.limiter, ft_strlen(ptr.limiter)))
			break ;
		ptr.buff = ft_strjoin(ptr.buff, ptr.line);
		free(ptr.line);
	}
	free(ptr.line);
	ptr.fd = open("...", O_CREAT | O_RDWR, 0777);
	if (!ptr.fd)
		exit (-1);
	write(ptr.fd, ptr.buff, ft_strlen(ptr.buff));
	free(ptr.buff);
	close(ptr.fd);
	ptr.fd = open("...", O_CREAT | O_RDONLY);
	if (!ptr.fd)
		exit (-1);
	if (unlink("...") < 0)
		perror("Failed to remove file");
	dup2(ptr.fd, STDIN_FILENO);
	ft_here_doc(ac, av, env);
}
