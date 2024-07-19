/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinaret <vkinaret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 00:10:46 by vkinaret          #+#    #+#             */
/*   Updated: 2024/07/19 03:21:34 by vkinaret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int  parse_coordinates(char *line)
{
    if (!line)
        return (1);
    return (0);
}

static int  parse_vector(char *line)
{
    if (!line)
        return (1);
    return (0);
}

static int  parse_fov(char *line)
{
    if (!line)
        return (1);
    return (0);
}

int parse_camera(char *line)
{
    while (*line == ' ')
        line++;
    if (parse_coordinates(line) == 1)
        return (print_error(COORDINATES));
    while (ft_isdigit(*line) || *line == ',' || *line == '-')
        line++;
    while (*line == ' ')
        line++;
    if (parse_vector(line) == 1)
        return (print_error(VECTOR));
    while (ft_isdigit(*line) || *line == ',' || *line == '-' || *line == '.')
        line++;
    while (*line == ' ')
        line++;
    if (parse_fov(line) == 1)
        return (print_error(FOV));
    while (ft_isdigit(*line))
        line++;
    if (*line != '\n')
        return (print_error(NEWLINE));
    return (0);
}
