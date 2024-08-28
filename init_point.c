/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_point.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinaret <vkinaret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 20:17:53 by vkinaret          #+#    #+#             */
/*   Updated: 2024/08/28 14:51:10 by vkinaret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static double   init_x(char *line, double x, double mod, double value)
{
    if (*line == '-')
    {
        mod = -1;
        line++;
    }
    while (ft_isdigit(*line))
    {
        value *= 10;
        value += ((*line) - '0');
        line++;
    }
    if (*line == '.')
    {
        line++;
        while (ft_isdigit(*line))
        {
            value += ((*line) - '0') * x;
            x = x * 0.1;
            line++;
        }
    }
    return (value * mod);
}

static double   init_y(char *line, double x, double mod, double value)
{
    if (*line == '-')
    {
        mod = -1;
        line++;
    }
    while (ft_isdigit(*line))
    {
        value *= 10;
        value += ((*line) - '0');
        line++;
    }
    if (*line == '.')
    {
        line++;
        while (ft_isdigit(*line))
        {
            value += ((*line) - '0') * x;
            x = x * 0.1;
            line++;
        }
    }
    return (value * mod);
}

static double   init_z(char *line, double x, double mod, double value)
{
    if (*line == '-')
    {
        mod = -1;
        line++;
    }
    while (ft_isdigit(*line))
    {
        value *= 10;
        value += ((*line) - '0');
        line++;
    }
    if (*line == '.')
    {
        line++;
        while (ft_isdigit(*line))
        {
            value += ((*line) - '0') * x;
            x = x * 0.1;
            line++;
        }
    }
    return (value * mod);
}

t_xyz    init_point(char *line)
{
    t_xyz   point;
    
    point.x = init_x(line, 0.1, 1, 0);
    if (*line == '-')
        line++;
    while (ft_isdigit(*line) || *line == '.')
        line++;
    if (*line == ',')
        line++;
    point.y = init_y(line, 0.1, 1, 0);
    if (*line == '-')
        line++;
    while (ft_isdigit(*line) || *line == '.')
        line++;
    if (*line == ',')
        line++;
    point.z = init_z(line, 0.1, 1, 0);
    return (point);
}
