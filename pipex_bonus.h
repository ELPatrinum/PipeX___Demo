/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muel-bak <muel-bak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:59:49 by muel-bak          #+#    #+#             */
/*   Updated: 2023/12/12 17:39:45 by muel-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct t_list
{
	int	i;
	int	y;
	int	g;
	int	j;
}	t_list;

char	*ft_error(char *av, char *av2);
char	*to_space(char *line);
char	*ft_strjoin(char const *s1, char const *s2);
int		valid_cmd(char *av);
void	first_cmd(char **av, char **env, int *pipid, int fd);
void	sec_cmd(char **av, char **env, int fd, int last);
void	mid_cmd_run(char **av, char **env, int *pipid, int arg);
void	mid_cmd(char **av, char **env, int args);
void	ft_puterror(char *str);
int		spaces(char *str);
int		ft_strlen(const char *str);
void	empty_or_space_error(char **av, char **env, int args);
int		pipex(char **av, char **env, int args);

#endif