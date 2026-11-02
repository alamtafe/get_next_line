#include "get_next_line.h"
#include <stdio.h>

int	ft_strlen(char const *s)
{
	int	i;

	if(!s)
		return (0);
	i = 0;
	while(s[i])
		i++;
	return (i);
}

int	ft_strrchr(char *s, char c)
{
	size_t	i;

	if (!s)
		return(0);
	i  = ft_strlen(s);
	while(i > 0 && s[i] != c)
		i--;
	if (s[i] == c)
		return(1);
	return(0);
}

char	*ft_strdup(char const *s)
{
	int	i;
	char	*str;

	if(!s)
		return(NULL);
	i = ft_strlen(s);
	str = malloc(i + 1);
	if (!str)
		return(NULL);
	i = 0;
	while(s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}


char *ft_realloc(char *ptr, size_t size)
{
	char	*new;
	size_t 		i;
	if(!ptr)
		return (malloc(size));
	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}
	new = malloc(size + 1);
	i = 0;
	while (i < size && ptr[i])
	{
		new[i] = ptr[i];
	}
	new[i] = '\0';
	free(ptr);
	return(new);
}
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int			i;
	char	*sub;

	if(!s)
		return (NULL);
	i = ft_strlen(s);
	if(len > start - i)
		len = start - i;
	sub = malloc(len + 1);
	if(!sub)
		return(NULL);
	i = 0;
	while(i < len && s[i + start])
	{
		sub[i] = s[i + start];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}
char	*append_buffer(char *line, char *buffer, size_t *length, size_t *capacity, size_t bytes_count)
{
	size_t	i;
	char	*tmp;
	size_t			required;

	required = *length + bytes_count + 1;
	if (required > *capacity)
	{
		tmp = realloc(line, required);
		if (!tmp)
			return (NULL);
		*capacity = required;
		line = tmp;
	}
	i = 0;
	while(i < bytes_count)
	{
		line[i + *length] = buffer[i];
		i++; 
	}
	line[i + *length] = '\0';
	*length = *length + i;
	return(line);
}