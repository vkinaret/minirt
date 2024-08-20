/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinaret <vkinaret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 20:18:24 by vkinaret          #+#    #+#             */
/*   Updated: 2024/08/20 20:19:00 by vkinaret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static double   str_to_double(char *ratio)
{
    double  x;
    double  value;

    x = 0.1;
    value = 0;
    if (*ratio == '1')
        value = 1;
    ratio++;
    if (*ratio == '.')
        ratio++;
    while (ft_isdigit(*ratio))
    {
        value += ((*ratio) - '0') * x;
        x = x * 0.1;
        ratio++;
    }
    return (value);
}

double   init_ratio(char *line, int i, int len)
{
    char    *ratio;
    double  value;

    while (ft_isdigit(line[i]) || line[i] == '.')
    {
        len++;
        i++;
    }
    ratio = ft_substr(line, 0, len);
    value = str_to_double(ratio);
    free(ratio);
    return (value);
}
