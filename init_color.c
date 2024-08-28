/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinaret <vkinaret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 19:50:25 by vkinaret          #+#    #+#             */
/*   Updated: 2024/08/28 14:51:17 by vkinaret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int  init_r(char *line)
{
    int value;

    value = 0;
    while (ft_isdigit(*line))
    {
        value *= 10;
        value += (*line) - '0';
        line++;
    }
    return (value);
}

static int  init_g(char *line)
{
    int value;

    value = 0;
    while (ft_isdigit(*line))
    {
        value *= 10;
        value += (*line) - '0';
        line++;
    }
    return (value);
}

static int  init_b(char *line)
{
    int value;

    value = 0;
    while (ft_isdigit(*line))
    {
        value *= 10;
        value += (*line) - '0';
        line++;
    }
    return (value);
}

static t_int    init_hex(int r, int g, int b)
{
    t_int   value;

    value = 0;
    value |= (r & 0xFF) << 16;
    value |= (g & 0xFF) << 8;
    value |= (b & 0xFF);
    return (value);
}

t_rgb    init_color(char *line)
{
    t_rgb   color;

    color.r = init_r(line);
    while (ft_isdigit(*line))
        line++;
    if (*line == ',')
        line++;
    color.g = init_g(line);
    while (ft_isdigit(*line))
        line++;
    if (*line == ',')
        line++;
    color.b = init_b(line);
    while (ft_isdigit(*line))
        line++;
    color.hex = 0;
    color.hex = init_hex(color.r, color.g, color.b);
    color.hex |= (color.r & 0xFF) << 16;
    color.hex |= (color.g & 0xFF) << 8;
    color.hex |= (color.b & 0xFF); 
    return (color);
}
