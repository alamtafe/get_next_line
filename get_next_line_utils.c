/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamtafe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 17:19:32 by alamtafe          #+#    #+#             */
/*   Updated: 2026/11/03 17:19:34 by alamtafe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char const *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_strrchr(char *s, char c)
{
	size_t	i;

	if (!s)
		return (0);
	i = ft_strlen(s);
	while (i > 0 && s[i] != c)
		i--;
	if (s[i] == c)
		return (1);
	return (0);
}

char	*ft_realloc(char *ptr, size_t size)
{
	char	*new;
	size_t	i;

	if (!ptr)
		return (malloc(size + 1));
	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}
	new = malloc(size + 1);
	if (!new)
		return (NULL);
	i = 0;
	while (i < size && ptr[i])
	{
		new[i] = ptr[i];
		i++;
	}
	new[i] = '\0';
	free(ptr);
	return (new);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*sub;

	if (!s)
		return (NULL);
	i = ft_strlen(s);
	if (len > start - i)
		len = start - i;
	sub = malloc(len + 1);
	if (!sub)
		return (NULL);
	i = 0;
	while (i < len && s[i + start])
	{
		sub[i] = s[i + start];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

char	*append_buffer(t_gnl *state, char *buffer, size_t bytes_count)
{
	size_t	i;
	char	*tmp;
	size_t	new_capacity;

	if (state->length + bytes_count + 1 > state->capacity)
	{
		new_capacity = state->capacity;
		while (new_capacity < state->length + bytes_count + 1)
			new_capacity *= 2;
		tmp = ft_realloc(state->line, new_capacity);
		if (!tmp)
			return (NULL);
		state->capacity = new_capacity;
		state->line = tmp;
	}
	i = 0;
	while (i < bytes_count)
	{
		state->line[i + state->length] = buffer[i];
		i++;
	}
	state->line[i + state->length] = '\0';
	state->length = state->length + i;
	return (state->line);
}
