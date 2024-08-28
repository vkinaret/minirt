/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_two.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinaret <vkinaret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 21:12:00 by vkinaret          #+#    #+#             */
/*   Updated: 2024/08/28 14:51:08 by vkinaret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_light  *init_light_two(t_light *light, char *content)
{
    while (*content == 'L' || *content == ' ')
        content++;
    light->point = init_point(content);
    while(ft_isdigit(*content) || *content == '.' || *content == ','
        || *content == '-')
        content++;
    while (*content == ' ')
        content++;
    light->ratio = init_ratio(content, 0);
    while (ft_isdigit(*content) || *content == '.')
        content++;
    while (*content == ' ')
        content++;
    light->color = init_color(content);
    return (light);
}

t_camera    *init_camera_two(t_camera *camera, char *content)
{
    while (*content == 'C' || *content == ' ')
        content++;
    camera->pov = init_point(content);
    while(ft_isdigit(*content) || *content == '.'
        || *content == ',' || *content == '-')
        content++;
    while (*content == ' ')
        content++;
    camera->vector = init_vector(content);
    while(ft_isdigit(*content) || *content == '.'
        || *content == ',' || *content == '-')
        content++;
    while (*content == ' ')
        content++;
    camera->fov = ft_atoi(content);
    return (camera);
}

t_object    *init_cylinder_two(t_object *cylinder, char *content)
{
    cylinder->diameter = init_diameter(content);
    while(ft_isdigit(*content) || *content == '.')
        content++;
    while (*content == ' ')
        content++;
    cylinder->height = init_height(content);
    while(ft_isdigit(*content) || *content == '.')
        content++;
    while (*content == ' ')
        content++;
    cylinder->color = init_color(content);
    cylinder->next = NULL;
    return (cylinder);
}
