/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinaret <vkinaret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 19:32:10 by vkinaret          #+#    #+#             */
/*   Updated: 2024/07/26 18:58:18 by vkinaret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int parse_coordinates(char *line, int i, int count)
{
    while (++count < 3)
    {
        i = 0;
        if (line[i] == '-')
            i++;
        while (ft_isdigit(line[i]))
            i++;
        if (line[i] == '.')
            i++;
        while (ft_isdigit(line[i]))
            i++;
        line += i;
        if (count < 2 && *line != ',')
            return (1);
        if (count == 2 && *line != ' ')
            return (1);
        line++;
    }
    return (0);
}

int parse_color(char *line, int i, int count)
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

int parse_ratio(char *line, int i)
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
