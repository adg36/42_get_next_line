/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razevedo <razevedo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:23:14 by razevedo          #+#    #+#             */
/*   Updated: 2025/11/06 14:03:19 by razevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		buffer[BUFFER_SIZE];
	ssize_t		bytes_read;
	int			j;
	char		*line;
	static char	*cache;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read <= 0 && *cache == '\0')
		return (NULL);
	j = 0;
	line = malloc(bytes_read + 1);
	while (bytes_read > 0 && buffer[j] != '\n')
	{
		line[j] = buffer[j];
		j++;
		bytes_read--;
	}
	if (buffer[j] == '\n')
	{
		line[j] = '\n';
		j++;
	}
	line[j] = '\0';
	return (line);
}

int main(void)
{
	int	file;

//	file = 0;
	file = open("test.txt", O_RDONLY);
	for (int i = 0; i < 1; i++)
		printf("%s", get_next_line(file));
}
