/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinaret <vkinaret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 21:40:34 by vkinaret          #+#    #+#             */
/*   Updated: 2024/08/17 20:18:49 by vkinaret         ###   ########.fr       */
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

static double   init_ratio(char *line, int i, int len)
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

static t_light	*init_ambient(t_list *list)
{
    t_list	*temp;
    t_light *ambient;
    char    *content;

    temp = list;
    ambient = malloc(sizeof(t_light));
    while (temp)
	{
        content = temp->content;
		if (!ft_strncmp(content, "A ", 2))
		{
            while (*content == 'A' || *content == ' ')
                content++;
            ambient->ratio = init_ratio(content, 0, 0);
            while (ft_isdigit(*content) || *content == '.')
                content++;
            while (*content == ' ')
                content++;
            ambient->color = init_color(content);
            return (ambient);
        }
		temp = temp->next;
	}
    free(ambient);
    return (NULL);
}

static t_light	*init_light(t_list *list)
{
    t_list	*temp;
    t_light *light;
    char    *content;

    temp = list;
    light = malloc(sizeof(t_light));
    while (temp)
	{
        content = temp->content;
		if (!ft_strncmp(content, "L ", 2))
		{
            while (*content == 'L' || *content == ' ')
                content++;
            light->point = init_coords(content);
            while(ft_isdigit(*content) || *content == '.'
                || *content == ',' || *content == '-')
                content++;
            while (*content == ' ')
                content++;
            light->ratio = init_ratio(content, 0, 0);
            while (ft_isdigit(*content) || *content == '.')
                content++;
            while (*content == ' ')
                content++;
            light->color = init_color(content);
            return (light);
        }
		temp = temp->next;
	}
    free(light);
    return (NULL);
}

t_scene	*init_struct(t_list *list, t_scene *scene)
{
	if (!list)
		return (NULL);
	scene = malloc(sizeof(t_scene));
	if (!scene)
		return (NULL); //malloc error
    scene->ambient = init_ambient(list);		
    scene->light = init_light(list);
    //scene->camera = init_camera(list);
    //scene->objects = init_objects(list);
	return (scene);
}
