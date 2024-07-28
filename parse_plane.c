/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinaret <vkinaret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 03:17:30 by vkinaret          #+#    #+#             */
/*   Updated: 2024/07/26 18:53:09 by vkinaret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int  iterate(int i, char *line, int mode)
{
    i++;
    if (mode == 0)
    {
        if (line[i] == '.' && ft_isdigit(line[i + 1]))
        {
            i++;
            while (ft_isdigit(line[i]))
                i++;
        }
    }
    if (mode == 1)
    {
        if (line[i] == '.' && line[i + 1] == '0')
        {
            i++;
            while (line[i] == '0')
                i++;
        }
    }
    return (i);
}

static int  parse_vector(char *line, int i, int count)
{
    while (++count < 3)
    {
        i = 0;
        if (line[i] == '-')
            i++;
        if (line[i] == '0')
            i = iterate(i, line, 0);
        else if (line[i] == '1')
            i = iterate(i, line, 1);
        line += i;
        if (count == 2 && *line != ',')
            return (0);
        if (count < 2 && *line != ',')
            return (1);
        line++;
    }
    return (1);
}

int parse_plane(char *line)
{
     while (*line == ' ')
        line++;
    if (parse_coordinates(line, 0, -1))
        return (print_error(COORDINATES, 17));
    while (ft_isdigit(*line) || *line == ',' || *line == '-' || *line == '.')
        line++;
    while (*line == ' ')
        line++;
    if (parse_vector(line, 0, -1))
        return (print_error(VECTOR, 18));
    while (ft_isdigit(*line) || *line == ',' || *line == '-' || *line == '.')
        line++;
    while (*line == ' ')
        line++;
    if (parse_color(line, 0, 0) == 1)
        return (print_error(COLOR, 19));
    while (ft_isdigit(*line) || *line == ',')
        line++;
    if (*line != '\n')
        return (print_error(NEWLINE, 20));
    return (0);
}
