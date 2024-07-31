/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinaret <vkinaret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 03:17:40 by vkinaret          #+#    #+#             */
/*   Updated: 2024/07/31 19:28:15 by vkinaret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int  parse_dimension(char *line, int i)
{
    while (ft_isdigit(line[i]))
        i++;
    if (line[i] == '.' && ft_isdigit(line[i + 1]))
    {
        i++;
        while (ft_isdigit(line[i]))
            i++;
    }
    if (line[i] == ' ')
        return (0);
    return (1);
}

int parse_sphere(char *line)
{
    while (*line == ' ')
        line++;
    if (parse_coordinates(line, 0, -1))
        return (print_error(COORDINATES, 21));
    while (ft_isdigit(*line) || *line == ',' || *line == '-' || *line == '.')
        line++;
    while (*line == ' ')
        line++;
    if (parse_dimension(line, 0))
        return (print_error(DIAMETER, 22));
    while (ft_isdigit(*line) || *line == '.')
        line++;
    while (*line == ' ')
        line++;
    if (parse_color(line, 0, 0) == 1)
        return (print_error(COLOR, 23));
    while (ft_isdigit(*line) || *line == ',')
        line++;
    if (*line != '\n')
        return (print_error(NEWLINE, 24));
    return (0);
}
