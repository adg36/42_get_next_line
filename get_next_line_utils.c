/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razevedo <razevedo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:24:36 by razevedo          #+#    #+#             */
/*   Updated: 2025/11/06 13:30:46 by razevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>

char	*ft_strchr(const char *s, int c)
{
	char			*ptr;
	unsigned char	uc;

	uc = (unsigned char)c;
	ptr = (char *)s;
	while (*ptr)
	{
		if (*ptr == uc)
			return (ptr);
		ptr++;
	}
	if (uc == '\0')
		return (ptr);
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*new_string;
	unsigned int	len;
	unsigned int	i;
	unsigned int	j;

	len = ft_strlen(s1) + ft_strlen(s2);
	new_string = malloc(len + 1);
	if (!new_string)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		new_string[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		new_string[i] = s2[j];
		i++;
		j++;
	}
	new_string[i] = '\0';
	return (new_string);
}
