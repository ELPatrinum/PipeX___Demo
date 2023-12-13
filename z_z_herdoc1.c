/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_z_herdoc1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muel-bak <muel-bak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 12:07:45 by muel-bak          #+#    #+#             */
/*   Updated: 2023/12/14 00:11:29 by muel-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "z_pipex_bonus.h"

int	ft_strlen_pro(char *str, int j, char c)
{
	int	i;

	i = j;
	if (!str)
		return (0);
	while (str[i] != '\0' && str[i] != c)
		i++;
	if (str[i] == c && c != '\0')
		i++;
	return (i);
}

int	new_line_check(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static char	*cpy_str(char *s1, char *s2, char *res)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	while (s2[j])
		res[i++] = s2[j++];
	res[i] = '\0';
	return (res);
}

char	*ft_strjoin_b(char *s1, char *s2)
{
	char	*res;

	if (!s1)
	{
		s1 = malloc(1 * sizeof(char));
		if (!s1)
		{
			free(s1);
			return (NULL);
		}
		s1[0] = '\0';
	}
	if (!s2)
		return (s1);
	res = malloc(ft_strlen_pro(s1, 0, '\0') + ft_strlen_pro(s2, 0, '\0') + 1);
	if (!res)
	{
		free(s1);
		return (NULL);
	}
	cpy_str(s1, s2, res);
	free(s1);
	return (res);
}
