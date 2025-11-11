/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razevedo <razevedo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:23:14 by razevedo          #+#    #+#             */
/*   Updated: 2025/11/10 14:38:39 by razevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include "get_next_line.h"

char	*get_line(char *cache, int len);

char	*get_next_line(int fd)
{
	char		*buffer;
	ssize_t		bytes_read;
	char		*line;
	int			len;
	static char	*cache;

	if (fd == -1)
		return (NULL);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (!cache)
			cache = ft_strdup(buffer);
		else
			cache = ft_strjoin(cache, buffer);
		if (ft_strchr(buffer, 10))
			break ;
	}
	if (bytes_read <= 0 && *cache == '\0')
		return (NULL);
	len = ft_strchr(cache, 10) - cache + 1;
	line = get_line(cache, len);
	cache = ft_substr(cache, len, ft_strlen(cache) - len);
	free(buffer);
	return (line);
}

char	*get_line(char *cache, int len)
{
	int		i;
	char	*line;

	i = 0;
	line = malloc(len + 1);
	while (cache[i] != '\n')
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

int main(void)
{
	int		file;
	char	*line;

//	file = 0;
	file = open("test.txt", O_RDONLY);
	if (!file)
	{
		printf("Could not open file.");
		return (1);
	}
	for (int i = 0; i < 10; i++)
	{
		line = get_next_line(file);
		printf("Line %i: >%s<\n", i, line);
	}
	free(line);
}
