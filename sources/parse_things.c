/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_things.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinaret <vkinaret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:35:05 by stuna             #+#    #+#             */
/*   Updated: 2024/11/12 17:12:31 by vkinaret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_camera(t_minilibx *mlx, char *str)
{
	t_camera	*elem;

	elem = secure_malloc(sizeof(t_camera));
	elem->next = NULL;
	mlx->cam = elem;
	next(&str);
	elem->o = parse_p3(&str);
	elem->nv = parse_p3(&str);
	in_range(elem->nv.x, -1, 1, "camera vector x");
	in_range(elem->nv.y, -1, 1, "camera vector y");
	in_range(elem->nv.z, -1, 1, "camera vector z");
	elem->nv = normalize(elem->nv);
	elem->fov = stoi(&str);
	in_range(elem->fov, 0, 180, "camera fov");
}

void	parse_light(t_scene **data, char *str)
{
	t_light	*elem;

	elem = secure_malloc(sizeof(t_light));
	elem->next = NULL;
	next(&str);
	elem->o = parse_p3(&str);
	elem->br = stof(&str);
	in_range(elem->br, 0, 1, "light");
	elem->color = parse_color(&str);
	(*data)->l = elem;
}

void	parse_ambient(t_scene *data, char *str)
{
	next(&str);
	data->ambient_light = stof(&str);
	in_range(data->ambient_light, 0, 1, "ambient lightning");
	data->al_color = parse_color(&str);
}
