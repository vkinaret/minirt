/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinaret <vkinaret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 20:57:44 by vkinaret          #+#    #+#             */
/*   Updated: 2024/08/23 23:07:35 by vkinaret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_object *init_cylinder(char *content)
{
    t_object    *cylinder;
    
    cylinder = malloc(sizeof(t_object));
    cylinder->id = 'C';
    while (*content == 'c' || *content == 'y' || *content == ' ')
        content++;
    cylinder->point = init_point(content);
    while(ft_isdigit(*content) || *content == '.'
        || *content == ',' || *content == '-')
        content++;
    while (*content == ' ')
        content++;
    cylinder->vector = init_vector(content);
    while(ft_isdigit(*content) || *content == '.'
        || *content == ',' || *content == '-')
        content++;
    while (*content == ' ')
        content++;
    return (init_cylinder_two(cylinder, content));
}

static t_object *init_sphere(char *content)
{
    t_object    *sphere;
    
    sphere = malloc(sizeof(t_object));
    sphere->id = 'S';
    while (*content == 's' || *content == 'p' || *content == ' ')
        content++;
    sphere->point = init_point(content);
    while(ft_isdigit(*content) || *content == '.'
        || *content == ',' || *content == '-')
        content++;
    while (*content == ' ')
        content++;
    sphere->diameter = init_diameter(content);
    while(ft_isdigit(*content) || *content == '.')
        content++;
    while (*content == ' ')
        content++;
    sphere->color = init_color(content);
    sphere->next = NULL;
    return (sphere);
}

static t_object *init_plane(char *content)
{
    t_object    *plane;
    
    plane = malloc(sizeof(t_object));
    plane->id = 'P';
    while (*content == 'p' || *content == 'l' || *content == ' ')
        content++;
    plane->point = init_point(content);
    while(ft_isdigit(*content) || *content == '.'
        || *content == ',' || *content == '-')
        content++;
    while (*content == ' ')
        content++;
    plane->vector = init_vector(content);
    while(ft_isdigit(*content) || *content == '.'
        || *content == ',' || *content == '-')
        content++;
    while (*content == ' ')
        content++;
    plane->color = init_color(content);
    plane->next = NULL;
    return (plane);
}

static void add_object(t_object **head, t_object *new)
{
    t_object    *temp;
    
    if (*head == NULL)
        *head = new;
    else
    {
        temp = *head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = new;
    }
}

t_object *init_objects(t_list *list, char *content)
{
    t_object    *head;
    t_object    *new;
    
    head = NULL;
    while (list)
	{
        new = NULL;
        content = list->content;
		if (!ft_strncmp(content, "pl ", 3))
            new = init_plane(content);
        else if (!ft_strncmp(content, "sp ", 3))
            new = init_sphere(content);
        else if (!ft_strncmp(content, "cy ", 3))
            new = init_cylinder(content);
        if (new != NULL)
            add_object(&head, new);
		list = list->next;
	}
    return (head);
}

