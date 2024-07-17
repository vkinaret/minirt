/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinaret <vkinaret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 21:03:27 by vkinaret          #+#    #+#             */
/*   Updated: 2024/07/17 16:17:08 by vkinaret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*trim_line(char *buffer, int index, int mode)
{
	int		i;
	char	*line;

	i = 0;
	if (mode == 1)
	{
		while (*buffer != '\0')
		{
			*buffer = *(buffer + index + 1);
			if (*buffer == '\0')
				break ;
			buffer++;
		}
		return (NULL);
	}
	line = ft_calloc(index + 1 + 1, 1);
	if (line == NULL)
		return (NULL);
	while (i <= index)
	{
		line[i] = buffer[i];
		i++;
	}
	return (line);
}

static char	*check_rv(int rv, char *buffer, char *line)
{
	if (line == NULL)
	{
		free(line);
		buffer[0] = '\0';
		return (NULL);
	}
	if (rv == 0 && line[0] != '\0')
	{
		if (line[0] == '\0')
		{
			free(line);
			return (NULL);
		}
		buffer[0] = '\0';
		return (line);
	}
	if (rv == -1 || rv == 0)
	{
		free(line);
		buffer[0] = '\0';
		return (NULL);
	}
	return (line);
}

static char	*initialize(char *buffer, int index, char *line)
{
	if (index == -1)
	{
		line = ft_strdup(buffer);
		if (line == NULL)
			return (NULL);
		return (line);
	}
	line = trim_line(buffer, index, 0);
	if (line == NULL)
		return (NULL);
	return (line);
}

static int	ft_index(char *buffer, int index)
{
	while (buffer[index] != '\n' && buffer[index] != '\0')
		index++;
	if (buffer[index] == '\0')
		index = -1;
	return (index);
}

char	*get_next_line(int fd, int rv, int index, char *line)
{
	static char	buffer[BUFFER_SIZE + 1];

	index = ft_index(buffer, 0);
	line = initialize(buffer, index, NULL);
	if (line == NULL)
		return (NULL);
	while (index == -1)
	{
		rv = read(fd, buffer, BUFFER_SIZE);
		if (rv == -1 || rv == 0)
			break ;
		if (rv < (int)ft_strlen(buffer))
			buffer[rv++] = '\0';
		index = ft_index(buffer, 0);
		line = ft_strjoin(line, buffer);
		if (line == NULL)
			return (check_rv(rv, buffer, line));
	}
	trim_line(buffer, index, 1);
	return (check_rv(rv, buffer, line));
}
