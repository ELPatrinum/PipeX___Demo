/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muel-bak <muel-bak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:39:46 by muel-bak          #+#    #+#             */
/*   Updated: 2023/12/12 12:52:59 by muel-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_error(char *av, char *av2)
{
	char	*res;
	t_list	ints;

	ints.j = 0;
	ints.g = 0;
	ints.i = 0;
	ints.y = 0;
	while (av[ints.j] != '\0' && av[ints.j] != ' ')
		ints.j++;
	while (av2[ints.g] != '\0' && av2[ints.g] != ' ')
		ints.g++;
	res = (char *)malloc(ints.j + ints.g + 3);
	if (res == NULL)
		return (perror("malloc"), NULL);
	while (av[ints.i] != '\0' && av[ints.i] != ' ')
	{
		res[ints.i] = av[ints.i];
		ints.i++;
	}
	res[ints.i++] = ':';
	res[ints.i++] = ' ';
	while (av2[ints.y] != '\0' && av2[ints.y] != ' ')
		res[ints.i++] = av2[ints.y++];
	res[ints.i] = '\0';
	return (res);
}

int	ft_strlen(const char *str)
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

char	*to_space(char *line)
{
	char	*res;
	int		j;
	int		i;

	j = 0;
	i = 0;
	while (line[j] != '\0' && line[j] != ' ')
		j++;
	res = (char *)malloc(j + 1);
	if (res == NULL)
	{
		perror("malloc");
		exit(1);
	}
	while (line[i] != '\0' && line[i] != ' ')
	{
		res[i] = line[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
