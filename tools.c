/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muel-bak <muel-bak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 15:31:32 by muel-bak          #+#    #+#             */
/*   Updated: 2023/12/10 15:32:42 by muel-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}
char	*join_it(char *str1, char *str2, char *joined)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str1[j] != '\0')
	{
		joined[i] = str1[j];
		i++;
		j++;
	}
	j = 0;
	while (str2[j] != '\0')
	{
		joined[i] = str2[j];
		i++;
		j++;
	}
	joined[i] = '\0';
	return (joined);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str1;
	char	*str2;
	char	*joined;

	if (!s1 && s2)
		return ((char *)s2);
	if (s1 && !s2)
		return ((char *)s1);
	if (!s1 && !s2)
		return (NULL);
	str1 = (char *)s1;
	str2 = (char *)s2;
	joined = malloc((ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (joined == NULL)
		return (NULL);
	else
		return (join_it(str1, str2, joined));
}
char *to_space(char *line)
{
	char *path;
	char *cmd;
    char *res;
    int j = 0;
    int i = 0;
	path = "/bin/";
    while (line[j] != '\0' && line[j] != ' ')
        j++;

    cmd = (char *)malloc(j + 1);
    if (cmd == NULL)
	{
        perror("malloc");
        exit(1);
    }

    while (line[i] != '\0' && line[i] != ' ')
	{
        cmd[i] = line[i];
        i++;
    }

    cmd[i] = '\0';
	res = ft_strjoin(path, cmd);
    return res;
}