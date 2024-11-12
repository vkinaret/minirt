/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stuna <stuna@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:02:09 by stuna             #+#    #+#             */
/*   Updated: 2024/11/11 17:30:07 by stuna            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_p3	configure_camera(int n, t_rss rss, t_minilibx mlx)
{
	double	aspect_ratio;
	double	fov_fix;
	double	x_off;
	double	y_off;
	t_p3	cam_pos;

	x_off = ((n % 3) * 0.5);
	y_off = ((n / 3) * 0.5);
	aspect_ratio = (double)(rss.xres) / (double)(rss.yres);
	fov_fix = tan((mlx.cam->fov * M_PI / 180) / 2);
	cam_pos.x = ((2 * ((rss.i + x_off) / rss.xres)) - 1)
		* aspect_ratio * fov_fix;
	cam_pos.y = (1 - (2 * ((rss.j + y_off) / rss.yres))) * fov_fix;
	cam_pos.x *= -1;
	cam_pos.z = 1;
	normalize(cam_pos);
	return (cam_pos);
}

static t_p3	adjust_view(t_p3 direction, t_p3 cam_normal)
{
	t_p3	x_axis;
	t_p3	y_axis;
	t_p3	z_axis;
	t_p3	temp;
	t_p3	rotated;

	temp = vdefine(0, 1, 0);
	z_axis = cam_normal;
	if (cam_normal.y == 1)
		x_axis = (t_p3){1, 0, 0};
	if (cam_normal.y == -1)
		x_axis = (t_p3){-1, 0, 0};
	else
		x_axis = cross(temp, z_axis);
	y_axis = cross(z_axis, x_axis);
	rotated.x = direction.x * x_axis.x + direction.y
		* y_axis.x + direction.z * z_axis.x;
	rotated.y = direction.x * x_axis.y + direction.y
		* y_axis.y + direction.z * z_axis.y;
	rotated.z = direction.x * x_axis.z + direction.y
		* y_axis.z + direction.z * z_axis.z;
	return (rotated);
}

int	compute_ray(int n, t_rss rss, t_wrapper *w)
{
	t_p3	direction;
	int		color;

	direction = configure_camera(n, rss, w->mlx);
	direction = adjust_view(direction, w->mlx.cam->nv);
	color = trace_ray(w->mlx.cam->o, direction, w);
	return (color);
}
