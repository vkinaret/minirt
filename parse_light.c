/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinaret <vkinaret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 00:53:34 by vkinaret          #+#    #+#             */
/*   Updated: 2024/07/31 19:28:23 by vkinaret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int parse_light(char *line)
{
    while (*line == ' ')
        line++;
    if (parse_coordinates(line, 0, -1) == 1)
        return (print_error(COORDINATES, 6));
    while (ft_isdigit(*line) || *line == ',' || *line == '-')
        line++;
    while (*line == ' ')
        line++;
    if (parse_ratio(line, 2) == 1)
        return (print_error(RATIO, 7));
    while (ft_isdigit(*line) || *line == '.')
        line++;
    while (*line == ' ')
        line++;
    if (parse_color(line, 0, 0) == 1)
        return (print_error(COLOR, 8));
    while (ft_isdigit(*line) || *line == ',')
        line++;
    if (*line != '\n')
        return (print_error(NEWLINE, 9));
    return (0);
}

int parse_ambient(char *line)
{
    while (*line == ' ')
        line++;
    if (parse_ratio(line, 2) == 1)
        return (print_error(RATIO, 10));
    while (ft_isdigit(*line) || *line == '.')
        line++;
    while (*line == ' ')
        line++;
    if (parse_color(line, 0, 0) == 1)
        return (print_error(COLOR, 11));
    while (ft_isdigit(*line) || *line == ',')
        line++;
    if (*line != '\n')
        return (print_error(NEWLINE, 12));
    return (0);
}
