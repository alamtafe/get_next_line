/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamtafe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 20:14:57 by alamtafe          #+#    #+#             */
/*   Updated: 2026/11/03 20:15:02 by alamtafe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_gnl
{
	char	*line;
	size_t	capacity;
	size_t	length;
}			t_gnl;

int			ft_strlen(char const *s);
int			ft_strrchr(char *s, char c);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strdup(char const *s);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*get_next_line(int fd);
char		*append_buffer(t_gnl *state, char *buffer, size_t bytes_count);
#endif