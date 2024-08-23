/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinaret <vkinaret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 21:40:34 by vkinaret          #+#    #+#             */
/*   Updated: 2024/08/23 22:51:25 by vkinaret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_scene *print_malloc_error(int code)
{
    printf("Error\n");
    if (code == 1)
        printf("(M1): Failed to malloc for data struct.\n");
    return (NULL);
}

static t_light	*init_ambient(t_list *list, char *content)
{
    t_light *ambient;

    ambient = malloc(sizeof(t_light));
    while (list)
	{
        content = list->content;
		if (!ft_strncmp(content, "A ", 2))
		{
            while (*content == 'A' || *content == ' ')
                content++;
            ambient->ratio = init_ratio(content, 0);
            while (ft_isdigit(*content) || *content == '.')
                content++;
            while (*content == ' ')
                content++;
            ambient->color = init_color(content);
            return (ambient);
        }
		list = list->next;
	}
    free(ambient);
    return (NULL);
}

static t_light	*init_light(t_list *list, char *content)
{
    t_light *light;

    light = malloc(sizeof(t_light));
    while (list)
	{
        content = list->content;
		if (!ft_strncmp(content, "L ", 2))
            return (init_light_two(light, content));
		list = list->next;
	}
    free(light);
    return (NULL);
}

static t_camera *init_camera(t_list *list, char *content)
{
    t_camera    *camera;

    camera = malloc(sizeof(t_camera));
    while (list)
	{
        content = list->content;
		if (!ft_strncmp(content, "C ", 2))
            return(init_camera_two(camera, content));
		list = list->next;
	}
    free(camera);
    return (NULL);
}

t_scene	*init_struct(t_list *list, t_scene *scene)
{
	if (!list)
		return (NULL);
	scene = malloc(sizeof(t_scene));
	if (!scene)
		return (print_malloc_error(1));
    scene->ambient = init_ambient(list, NULL);		
    scene->light = init_light(list, NULL);
    scene->camera = init_camera(list, NULL);
    scene->objects = init_objects(list, NULL);
	return (scene);
}
