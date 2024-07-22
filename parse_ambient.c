/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinaret <vkinaret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 23:36:17 by vkinaret          #+#    #+#             */
/*   Updated: 2024/07/22 20:31:46 by vkinaret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int parse_color(char *line, int i, int count)
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

static int parse_ratio(char *line, int i)
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

int parse_ambient(char *line)
{
    while (*line == ' ')
        line++;
    if (parse_ratio(line, 2) == 1)
        return (print_error(RATIO));
    while (ft_isdigit(*line) || *line == '.')
        line++;
    while (*line == ' ')
        line++;
    if (parse_color(line, 0, 0) == 1)
        return (print_error(COLOR));
    while (ft_isdigit(*line) || *line == ',')
        line++;
    if (*line != '\n')
        return (print_error(NEWLINE));
    return (0);
}
