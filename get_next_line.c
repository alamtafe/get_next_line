/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamtafe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 17:19:03 by alamtafe          #+#    #+#             */
/*   Updated: 2026/11/03 17:19:04 by alamtafe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*clear(char **line, char *content, size_t *capacity)
{
	free(content);
	free(*line);
	*capacity = 0;
	*line = NULL;
	return (NULL);
}

char	*sparater(char **line, size_t *capacity)
{
	char	*tmp;
	char	*temp;
	int		i;

	i = 0;
	while ((*line)[i] != '\n')
		i++;
	i++;
	tmp = ft_substr(*line, 0, i);
	if (!tmp)
	{
		return (clear(line, tmp, capacity));
	}
	temp = *line;
	*line = ft_substr(*line, i, ft_strlen(*line) - i);
	if (!*line)
	{
		return (clear(&tmp, temp, capacity));
	}
	*capacity = ft_strlen(*line) + 1;
	free(temp);
	return (tmp);
}

char	*eof_handle(char **line, char *buffer, size_t *capacity, char **res)
{
	char	*tmp;

	tmp = ft_substr(*line, 0, ft_strlen(*line));
	if (tmp)
	{
		*res = tmp;
		if (!tmp[0])
		{
			free(tmp);
			*res = NULL;
		}
		clear(line, buffer, capacity);
		return (*res);
	}
	return (clear(line, buffer, capacity));
}

char	*read_buffer(int fd, t_gnl *state, char *buffer, char **res)
{
	int		bytes_count;
	char	*tmp;

	buffer[0] = '\0';
	state->length = ft_strlen(state->line);
	while (!ft_strrchr(buffer, '\n'))
	{
		bytes_count = read(fd, buffer, BUFFER_SIZE);
		if (bytes_count < 0)
			return (clear(&state->line, buffer, &state->capacity));
		else if (bytes_count > 0)
			buffer[bytes_count] = '\0';
		else if (bytes_count == 0)
			return (eof_handle(&state->line, buffer, &state->capacity, res));
		tmp = append_buffer(state, buffer, bytes_count);
		if (!tmp)
			return (clear(&state->line, buffer, &state->capacity));
		state->line = tmp;
	}
	free(buffer);
	return (sparater(&state->line, &state->capacity));
}

char	*get_next_line(int fd)
{
	char			*buffer;
	char			*res;
	static t_gnl	state;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (ft_strrchr(state.line, '\n'))
		return (sparater(&state.line, &state.capacity));
	if (state.capacity == 0)
	{
		state.line = malloc(100);
		if (!state.line)
			return (NULL);
		state.line[0] = '\0';
		state.capacity = 100;
	}
	buffer = malloc((size_t)BUFFER_SIZE + 1);
	if (!buffer)
		return (clear(&state.line, buffer, &state.capacity));
	return (read_buffer(fd, &state, buffer, &res));
}
