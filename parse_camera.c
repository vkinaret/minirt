/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinaret <vkinaret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 00:10:46 by vkinaret          #+#    #+#             */
/*   Updated: 2024/07/22 20:58:16 by vkinaret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int  parse_coordinates(char *line, int i, int count)
{
    while (++count < 3)
    {
        i = 0;
        if (line[i] == '-')
            i++;
        while (ft_isdigit(line[i]))
            i++;
        if (line[i] == '.')
            i++;
        while (ft_isdigit(line[i]))
            i++;
        line += i;
        if (count < 2 && *line != ',')
            return (1);
        if (count == 2 && *line != ' ')
            return (1);
        line++;
    }
    return (0);
}

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
        if (line[i] == '.' && line[i + 2] == '0')
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

static int  parse_fov(char *line, int i)
{
    while (ft_isdigit(line[i]))
            i++;
    if (i == 0 || i > 3 || (i == 3 && ft_strncmp(line, "180", i) < 0))
            return (1);
    return (0);
}

int parse_camera(char *line)
{
    while (*line == ' ')
        line++;
    if (parse_coordinates(line, 0, -1))
        return (print_error(COORDINATES));
    while (ft_isdigit(*line) || *line == ',' || *line == '-' || *line == '.')
        line++;
    while (*line == ' ')
        line++;
    if (parse_vector(line, 0, -1))
        return (print_error(VECTOR));
    while (ft_isdigit(*line) || *line == ',' || *line == '-' || *line == '.')
        line++;
    while (*line == ' ')
        line++;
    if (parse_fov(line, 0))
        return (print_error(FOV));
    while (ft_isdigit(*line))
        line++;
    if (*line != '\n')
        return (print_error(NEWLINE));
    return (0);
}
