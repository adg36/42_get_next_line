/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razevedo <razevedo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:23:14 by razevedo          #+#    #+#             */
/*   Updated: 2025/11/18 15:26:28 by razevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include "get_next_line.h"

char	*ft_get_line(char *cache, int line_len);
char	*del_and_free(char *cache, int line_len);
int		error_handling(int fd, ssize_t bytes_read, char *buffer, char **cache);

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*line;
	ssize_t		bytes_read;
	int			line_len;
	static char	*cache;

	if (fd == -1 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	bytes_read = 1;
	if (error_handling(fd, bytes_read, buffer, &cache) == 1)
		return (NULL);
	if (!ft_strchr(cache, 10))
		line_len = ft_strlen(cache);
	else
		line_len = ft_strchr(cache, 10) - cache + 1;
	line = ft_get_line(cache, line_len);
	cache = del_and_free(cache, line_len);
	return (free(buffer), line);
}

int	error_handling(int fd, ssize_t bytes_read, char *buffer, char **cache)
{
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == 0 && (!*cache || **cache == '\0'))
			return (free(buffer), 1);
		if (bytes_read == -1)
		{
			free(*cache);
			*cache = NULL;
			return (free(buffer), 1);
		}
		if (bytes_read > 0)
		{
			if (!*cache)
				*cache = ft_strdup(buffer);
			else
			{
				buffer[bytes_read] = 0;
				*cache = ft_strjoin(*cache, buffer);
			}
		}
		if (ft_strchr(buffer, 10))
			break ;
	}
	return (0);
}

char	*ft_get_line(char *cache, int line_len)
{
	int		i;
	char	*line;

	i = 0;
	line = malloc(line_len + 1);
	if (!line)
	{
		cache = NULL;
		return (NULL);
	}
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
	free(cache);
	return (new_cache);
}
/*
int main(void)
{
	char	*line;

	while ((line = get_next_line(0)) != NULL) // 0 = stdin
	{
		printf("LINE: %s", line);
		free(line);
	}
	return (0);
}



int	main(void)
{
	int			fd_test;
	char	*str;

	fd_test = open("one_line_no_nl.txt", O_RDONLY);
	while (1)
	{
		str = get_next_line(fd_test);
		printf("lap: >%s<\n",str);
		if (str == NULL)
			break;
		free(str);
	}
	return (0);
}

int main(void)
{
	int		file;
	char	*line;
	int		i;

	file = open("1char.txt", O_RDONLY);
	if (!file)
	{
		printf("Could not open file.");
		return (1);
	}
	i = 0;
	line = get_next_line(file);
	while (line)
	{
		printf("Line %i: >%s<\n", i, line);
		free(line);
		line = get_next_line(file);
		i++;
	}
	printf("Line %i: >%s<\n", i, line);
	free(line);
	line = get_next_line(file);
	i++;
	free(line);
}*/
