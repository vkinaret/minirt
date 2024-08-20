/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinaret <vkinaret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 20:18:24 by vkinaret          #+#    #+#             */
/*   Updated: 2024/08/20 21:21:56 by vkinaret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//init ratio should handle negatives (vector range -1 to 1)

double   init_ratio(char *line)
{
    double  x;
    double  value;

    x = 0.1;
    value = 0;
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
    return (value);
}

t_xyz  init_vector(char *line)
{
    t_xyz   vector;

    vector.x = init_ratio(line);
    while (ft_isdigit(*line) || *line == '.' || *line == '-')
        line++;
    if (*line == ',')
        line++;
    vector.y = init_ratio(line);
    while (ft_isdigit(*line) || *line == '.' || *line == '-')
        line++;
    if (*line == ',')
        line++;
    vector.z = init_ratio(line);
    return (vector);
}

