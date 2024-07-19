/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinaret <vkinaret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 00:53:34 by vkinaret          #+#    #+#             */
/*   Updated: 2024/07/19 03:21:19 by vkinaret         ###   ########.fr       */
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
        if (i > 3 || ft_strncmp(line, "255", i) > 0)
            return (1);
        line += i;
        if (count < 2 && *line != ',')
            return (1);
        if (count == 2 && *line == ',')
            return (1);
        line++;
        count++;
    }
    return (0);
}

static int parse_ratio(char *line)
{
    int i;

    i = 2;
    if (line[0] == '0' && line[1] == '.')
    {
        while (ft_isdigit(line[i]))
            i++;
    }
    else if (line[0] == '1' && line[1] == '.')
    {
        while (line[i] == '0')
            i++;
    }
    if (line[i] == ' ')
        return (0);
    return (1);
}

static int  parse_coordinates(char *line)
{
    if (!line)
        return (1);
    return (0);
}

int parse_light(char *line)
{
    while (*line == ' ')
        line++;
    if (parse_coordinates(line) == 1)
        return (print_error(COORDINATES));
    while (ft_isdigit(*line) || *line == ',' || *line == '-')
        line++;
    while (*line == ' ')
        line++;
    if (parse_ratio(line) == 1)
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
