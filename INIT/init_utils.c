/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinaret <vkinaret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 20:18:24 by vkinaret          #+#    #+#             */
/*   Updated: 2024/08/23 22:47:35 by vkinaret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double   init_ratio(char *line, int flag)
{
    double  x;
    double  mod;
    double  value;

    x = 0.1;
    mod = 1;
    value = 0;
    if (flag == 1 && *line == '-')
    {
        mod = -1;
        line++;
    }
    if (*line == '1')
        value = 1;
    line++;
    if (*line == '.')
        line++;
    while (ft_isdigit(*line))
    {
        value += ((*line) - '0') * x;
        x = x * 0.1;
        line++;
    }
    return (value * mod);
}

t_xyz  init_vector(char *line)
{
    t_xyz   vector;

    vector.x = init_ratio(line, 1);
    while (ft_isdigit(*line) || *line == '.' || *line == '-')
        line++;
    if (*line == ',')
        line++;
    vector.y = init_ratio(line, 1);
    while (ft_isdigit(*line) || *line == '.' || *line == '-')
        line++;
    if (*line == ',')
        line++;
    vector.z = init_ratio(line, 1);
    return (vector);
}

double  init_diameter(char *line)
{
    double  x;
    double  value;

    x = 0.1;
    value = 0;
    while (ft_isdigit(*line))
    {
        value *= 10;
        value += (*line) - '0';
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
    return (value);
}

double  init_height(char *line)
{
    double  x;
    double  value;

    x = 0.1;
    value = 0;
    while (ft_isdigit(*line))
    {
        value *= 10;
        value += (*line) - '0';
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
    return (value);
}

