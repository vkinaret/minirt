/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinaret <vkinaret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 03:17:51 by vkinaret          #+#    #+#             */
/*   Updated: 2024/07/31 19:28:28 by vkinaret         ###   ########.fr       */
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

int parse_cylinder(char *line)
{
    while (*line == ' ')
        line++;
    if (parse_coordinates(line, 0, -1))
        return (print_error(COORDINATES, 25));
    while (ft_isdigit(*line) || *line == ',' || *line == '-' || *line == '.')
        line++;
    while (*line == ' ')
        line++;
    if (parse_vector(line, 0, -1))
        return (print_error(VECTOR, 26));
    while (ft_isdigit(*line) || *line == ',' || *line == '-' || *line == '.')
        line++;
    while (*line == ' ')
        line++;
    if (parse_dimension(line, 0))
        return (print_error(DIAMETER, 29));
    while (ft_isdigit(*line) || *line == '.')
        line++;
    while (*line == ' ')
        line++;
    if (parse_dimension(line, 0))
        return (print_error(HEIGHT, 30));
    while (ft_isdigit(*line) || *line == '.')
        line++;
    while (*line == ' ')
        line++;
    if (parse_color(line, 0, 0) == 1)
        return (print_error(COLOR, 27));
    while (ft_isdigit(*line) || *line == ',')
        line++;
    if (*line != '\n')
        return (print_error(NEWLINE, 28));
    return (0);
}
