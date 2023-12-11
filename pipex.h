#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>

char	*ft_error(char *av, char *av2);
char	*to_space(char *line);
char	*ft_strjoin(char const *s1, char const *s2);

#endif