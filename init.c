/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinaret <vkinaret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 21:40:34 by vkinaret          #+#    #+#             */
/*   Updated: 2024/08/20 21:24:16 by vkinaret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
            ambient->ratio = init_ratio(content);
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
		{
            while (*content == 'L' || *content == ' ')
                content++;
            light->point = init_point(content);
            while(ft_isdigit(*content) || *content == '.'
                || *content == ',' || *content == '-')
                content++;
            while (*content == ' ')
                content++;
            light->ratio = init_ratio(content);
            while (ft_isdigit(*content) || *content == '.')
                content++;
            while (*content == ' ')
                content++;
            light->color = init_color(content);
            return (light);
        }
		list = list->next;
	}
    free(light);
    return (NULL);
}

//typedef struct s_camera
//{
//	t_xyz	pov;
//	t_xyz	vector;
//	int		fov;
//}				t_camera;
//C -50,0,20 0,0,0 70

static t_camera *init_camera(t_list *list, char *content)
{
    t_camera *camera;

    camera = malloc(sizeof(t_camera));
    while (list)
	{
        content = list->content;
		if (!ft_strncmp(content, "C ", 2))
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
		return (NULL); //malloc error
    scene->ambient = init_ambient(list, NULL);		
    scene->light = init_light(list, NULL);
    scene->camera = init_camera(list, NULL);
    //scene->objects = init_objects(list);
	return (scene);
}
