/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinaret <vkinaret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 19:32:10 by vkinaret          #+#    #+#             */
/*   Updated: 2024/07/31 19:15:31 by vkinaret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int parse_coordinates(char *line, int i, int count)
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

int parse_color(char *line, int i, int count)
{
    while (count < 3)
    {
        i = 0;
        while (ft_isdigit(line[i]))
            i++;
        if (i == 0 || i > 3 || (i == 3 && ft_strncmp(line, "255", i) > 0))
            return (1);
        line += i;
        if (count < 2 && *line != ',')
            return (1);
        if (count == 2 && *line != '\n')
            return (1);
        line++;
        count++;
    }
    return (0);
}

int parse_ratio(char *line, int i)
{
    if (line[0] == '0')
    {
        i++;
        if (line[1] == '.' && ft_isdigit(line[i]))
        {
            i++;
            while (ft_isdigit(line[i]))
                i++;
        }
    }
    else if (line[0] == '1')
    {
        i++;
        if (line[1] == '.' && line[i] == '0')
        {
            i++;
            while (line[i] == '0')
                i++;
        }
    }
    if (line[i] == ' ')
        return (0);
    return (1);
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
        if (line[i] == '.' && line[i + 1] == '0')
        {
            i++;
            while (line[i] == '0')
                i++;
        }
    }
    return (i);
}

int  parse_vector(char *line, int i, int count)
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
