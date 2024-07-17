/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinaret <vkinaret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 21:03:27 by vkinaret          #+#    #+#             */
/*   Updated: 2024/07/16 16:00:07 by vkinaret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	new_line(char *str, int mode)
{
	int	i;

	i = 0;
	if (mode == 0)
	{
		if (str == NULL)
			return (0);
		while (str[i] != '\0')
			i++;
	}
	if (mode == 1)
	{
		while (str[i] != '\n')
		{
			if (str[i] == '\0')
				return (-1);
			i++;
		}
	}
	return (i);
}

static char	*join(char *temp, char *line, char *buffer)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	while (line[i] != '\0')
	{
		temp[i] = line[i];
		i++;
	}
	free(line);
	j = 0;
	while (buffer[j] != '\0')
	{
		temp[i + j] = buffer[j];
		if (temp[i + j] == '\n')
			break ;
		j++;
	}
	result = ft_strdup(temp);
	if (result == NULL)
		return (NULL);
	return (result);
}

static char	*strjoin(char *line, char *buffer)
{
	int		size;
	char	*temp;
	char	*result;

	if (line == NULL && buffer != NULL)
		return (ft_strdup(buffer));
	if (line != NULL && buffer == NULL)
		return (ft_strdup(line));
	size = new_line(line, 0) + new_line(buffer, 0);
	temp = ft_calloc(size + 1, 1);
	if (temp == NULL)
	{
		free(line);
		return (NULL);
	}
	result = join(temp, line, buffer);
	if (result == NULL)
	{
		free(temp);
		return (NULL);
	}
	free(temp);
	return (result);
}

static void	trim_buffer(char *buffer, int index)
{
	while (*buffer != '\0')
	{
		*buffer = *(buffer + index + 1);
		if (*buffer == '\0')
			break ;
		buffer++;
	}
}

static char	*trim_line(char *buffer, int index)
{
	int		i;
	char	*line;

	i = 0;
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

static char	*initialize(char *buffer, int index)
{
	char	*line;

	line = NULL;
	if (index == -1)
	{
		line = ft_strdup(buffer);
		if (line == NULL)
			return (NULL);
	}
	else
	{
		line = trim_line(buffer, index);
		if (line == NULL)
			return (NULL);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	int			rv;
	int			index;
	char		*line;
	static char	buffer[BUFFER_SIZE + 1];

	index = new_line(buffer, 1);
	line = initialize(buffer, index);
	if (line == NULL)
		return (NULL);
	while (index == -1)
	{
		rv = read(fd, buffer, BUFFER_SIZE);
		if (rv == -1 || rv == 0)
			break ;
		if (rv < new_line(buffer, 0))
			buffer[rv++] = '\0';
		index = new_line(buffer, 1);
		line = strjoin(line, buffer);
		if (line == NULL)
			return (check_rv(rv, buffer, line));
	}
	trim_buffer(buffer, index);
	return (check_rv(rv, buffer, line));
}

/*int main(int argc, char **argv)
{
    int fd;
    char *rv;

    rv = ft_calloc(BUFFER_SIZE + 1, 1);
    if (argc < 2)
    {
        printf("Not enough arguments.\n");
    }
    if (argc == 2)
    {
        fd = open(argv[1], O_RDONLY);
        while (rv != NULL)
        {
            rv = get_next_line(fd);
            printf("Result: %s\n", rv);
        }
        close(fd);
    }
    if (argc > 2)
    {
        printf("Too many arguments.\n");
    }
    return (0);
}*/