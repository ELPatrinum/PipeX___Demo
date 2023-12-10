#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <stdio.h>

char	*ft_strjoin(char const *s1, char const *s2);
char	*to_space(char *line);
size_t	ft_strlen(const char *str);
char	**ft_split(char const *s, char c);

#endif