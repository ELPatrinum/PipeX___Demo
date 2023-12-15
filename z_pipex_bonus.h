/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_pipex_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muel-bak <muel-bak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:59:49 by muel-bak          #+#    #+#             */
/*   Updated: 2023/12/14 08:35:55 by muel-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef Z_PIPEX_BONUS_H
# define Z_PIPEX_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

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

typedef struct t_ptr
{
	char	*limiter;
	char	*line;
	char	*buff;
	int		fd;
}	t_ptr;

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
int		ft_strncmp(const char *str1, const char *str2, size_t n);

void	here_first_cmd(char **av, char **env, int *pipid);
void	here_sec_cmd(char **av, char **env, int fd, int last);
int		here_doc_pipex(char **av, char **env, int args);
int		ft_here_doc(int ac, char **av, char **env);
void	run_here_doc(int ac, char **av, char **env, t_ptr ptr);

char	*get_next_line(int fd);
char	*get_remains(char *remains);
char	*get_theline(char *str);
char	*read_from_fd(int fd, char *res);
int		ft_strlen_pro(char *s, int j, char c);
int		new_line_check(char *str);
char	*ft_strjoin_b(char *s1, char *s2);

#endif