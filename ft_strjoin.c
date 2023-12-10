/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muel-bak <muel-bak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 12:48:01 by muel-bak          #+#    #+#             */
/*   Updated: 2023/12/10 15:27:37 by muel-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}
static char	*join_it(char *str1, char *str2, char *joined)
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
