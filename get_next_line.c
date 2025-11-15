/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razevedo <razevedo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:23:14 by razevedo          #+#    #+#             */
/*   Updated: 2025/11/14 16:05:26 by razevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include "get_next_line.h"

char	*ft_get_line(char *cache, int line_len);
char	*del_and_free(char *cache, int line_len);
int		get_line_length(char *cache);

char	*get_next_line(int fd)
{
	char		*buffer;
	ssize_t		bytes_read;
	char		*line;
	int			line_len;
	static char	*cache;

	if (fd == -1 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (!cache && bytes_read > 0)
			cache = ft_strdup(buffer);
		else
		{
			if (bytes_read > 0)
			{
				buffer[bytes_read] = 0;
				cache = ft_strjoin(cache, buffer);
			}
			else
				break ;
		}
		if (ft_strchr(buffer, 10))
			break ;
	}
	if (bytes_read <= 0)
	{
		if (!cache || *cache == '\0')
		{
			free(buffer);
			return (NULL);
		}
	}
	line_len = get_line_length(cache);
	line = ft_get_line(cache, line_len);
	cache = del_and_free(cache, line_len);
	free(buffer);
	return (line);
}

int		get_line_length(char *cache)
{
	if (!ft_strchr(cache, 10))
		return (ft_strlen(cache));
	else
		return (ft_strchr(cache, 10) - cache + 1);
}

char	*ft_get_line(char *cache, int line_len)
{
	int		i;
	char	*line;

	i = 0;
	line = malloc(line_len + 1);
	/*if (!line)
	{
		free(cache);
		return (NULL);
	}*/
	while (cache[i] != '\n' && cache[i] != '\0')
	{
		line[i] = cache[i];
		i++;
	}
	if (cache[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

void	*ft_calloc(size_t nelem, size_t elsize)
{
	unsigned char	*arr;
	size_t			i;

	if (elsize != 0 && nelem > (SIZE_MAX - 1) / elsize)
		return (NULL);
	arr = malloc(nelem * elsize);
	if (!arr)
		return (NULL);
	i = 0;
	while (i < nelem * elsize)
	{
		arr[i] = 0;
		i++;
	}
	return ((void *)arr);
}

char	*del_and_free(char *cache, int line_len)
{
	char	*new_cache;

	new_cache = ft_substr(cache, line_len, ft_strlen(cache) - line_len);
	if (cache != NULL)
		free(cache);
	return (new_cache);
}
/*
int main(void)
{
	int		file;
	char	*line;
	int		i;

//	file = 0;
	file = open("1char.txt", O_RDONLY);
	if (!file)
	{
		printf("Could not open file.");
		return (1);
	}
	// for (int i = 0; i < 10; i++)
	i = 0;
	line = get_next_line(file);
	while (line)
	{
		printf("Line %i: >%s<\n", i, line);
		free(line);
		line = get_next_line(file);
		i++;
	}	
	free(line);
}*/
