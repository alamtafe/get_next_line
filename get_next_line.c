#include "get_next_line.h"

char	*sparater(char  **line, size_t *length, size_t *capacity)
{
	char *tmp;
	char *temp;
	int i;

	i = 0;
	while((*line)[i] != '\n')
		i++;
	i++;
	tmp = ft_substr(*line, 0, i);
	if (!tmp)
	{
		free(*line);
    	*line = NULL;
    	*capacity = 0;
    	return (NULL);
	}
	*length = ft_strlen(*line) - i;
	temp = *line;
	*line = ft_substr(*line, i, *length);
	if(!*line)
	{
		 *capacity = 0;
		free(temp);
    	free(tmp);
    	return (NULL);
	}
	*capacity = *length + 1;
	free(temp);
	return (tmp);
}
char	*clear(char **line, char *content,size_t *capacity)
{
		free(content);
		free(*line);
		*capacity = 0;
		*line = NULL;
		return (NULL);

}
int	first_read(int fd, char **line, char *buffer, size_t *length, size_t *capacity, char **res)
{
	int		bytes_count;
	char	*tmp;

	bytes_count = read(fd, buffer, BUFFER_SIZE);
	if (bytes_count < 0)
	{
		*line = clear(line, buffer, capacity);
		return(-1);
	}
	else if (bytes_count > 0)
		buffer[bytes_count] = '\0';
	else if (bytes_count == 0)
	{
		tmp = ft_strdup(*line);
		if (tmp)
		{
			if(tmp[0])
			{
				*line = (clear(line, buffer, capacity));
				*res = tmp;
				return(1);
			}
			else 
			{
				free(tmp);
				*res = NULL;
				*line = (clear(line, buffer, capacity));
				return(1);
			}
		}
		*line = clear(line, buffer, capacity);
		return(-1);
	}
	tmp = append_buffer(*line, buffer, length, capacity, bytes_count);
	if (!tmp)
	{
		*line = clear(line, buffer, capacity);
		return(-1);
	}
	*line = tmp;
	return (0);
}


char	*get_next_line(int fd)
{
	char			*buffer;
	char			*res;
	char			*tmp;
	int				bytes_count;
	int				status;
	size_t			length;
	static t_gnl	state;

	if (!state.line)
		length = 0;
	else
		length = ft_strlen(state.line);
	if (ft_strrchr(state.line, '\n'))
		return (sparater(&state.line, &length, &state.capacity));
	if (state.capacity == 0)
	{
		state.line = malloc(100);
		if (!state.line)
			return (NULL);
		state.line[0] = '\0';
		state.capacity = 100;
	}
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (clear(&state.line, buffer, &state.capacity));
	status = first_read(fd, &state.line, buffer, &length,
			&state.capacity, &res);
	if (status == 1)
		return (res);
	else if (status == -1)
		return (NULL);
	while (!ft_strrchr(buffer, '\n'))
	{
		bytes_count = read(fd, buffer, BUFFER_SIZE);
		if (bytes_count < 0)
		{
			free(buffer);
			free(state.line);
			state.line = NULL;
			state.capacity = 0;
			return (NULL);
		}
		else if (bytes_count > 0)
			buffer[bytes_count] = '\0';
		else if (bytes_count == 0)
		{
			tmp = ft_strdup(state.line);
			if (tmp)
			{
				free(buffer);
				free(state.line);
				state.line = NULL;
				state.capacity = 0;
				return (tmp);
			}
			free(buffer);
			free(state.line);
			state.line = NULL;
			state.capacity = 0;
			return (NULL);
		}
		state.line = append_buffer(state.line, buffer, &length,
				&state.capacity, bytes_count);
		if (!state.line)
		{
			free(buffer);
			return (NULL);
		}
	}
	free(buffer);
	return (sparater(&state.line, &length, &state.capacity));
}

#include <stdio.h>
#include <fcntl.h>


// int main(void)
// {
//     char *line;
//     int fd = open("file.txt", O_RDONLY);
// 	int f = open("output.txt", O_WRONLY);
//     if (fd == -1)
//         return (1);
// 	while ((line = get_next_line(fd)))
// 	{
// 		write(f, line, ft_strlen(line));
// 		printf("[%s]", line);
// 		free(line);
// 	}
//     close(fd);
//     return (0);
// }