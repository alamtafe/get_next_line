#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

typedef struct s_gnl
{
    char    *line;
    size_t  capacity;
}   t_gnl;

int     ft_strlen(char const *s);
int     ft_strrchr(char *s, char c);
char    *ft_strjoin(char const *s1, char const *s2);
char    *ft_strdup(char const *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char    *get_next_line(int fd);
char	*append_buffer(char *line, char *buffer, size_t *length, size_t *capacity, size_t bytes_count);

#endif
