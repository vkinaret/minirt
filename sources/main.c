/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinaret <vkinaret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:30:15 by stuna             #+#    #+#             */
/*   Updated: 2024/11/12 16:49:43 by vkinaret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	trace_ray(t_p3 o, t_p3 d, t_wrapper *w)
{
	t_v3		ray;
	t_figures	cl_fig;
	t_inter		inter;
	double		closest_intersection;

	ray.o = o;
	ray.d = d;
	closest_intersection = INFINITY;
	cl_fig.flag = -1;
	try_all_intersections(ray, w->lst, &cl_fig, &closest_intersection);
	inter.p = vadd(o, scal_x_vec(closest_intersection, d));
	calc_normal(inter.p, d, &(inter.normal), &cl_fig);
	if (cl_fig.flag != -1)
		inter.color = cl_fig.color;
	else
		inter.color = w->data.bgr;
	compute_light(&inter, w->data, w->lst);
	return (adjust_color_brightness(inter.color, 1));
}

int	calc_pixel_color(int *edge_color, int last[2], t_wrapper *w)
{
	t_rss	rss;
	int		*color;

	rss.limit = 3;
	rss.xres = w->data.xres;
	rss.yres = w->data.yres;
	rss.i = w->i;
	rss.j = w->j;
	w->data.bgr = 0x202020;
	color = compute_pixel_sample(edge_color, last, rss, w);
	if (calculate_color_difference(color[0], color[3])
		|| calculate_color_difference(color[1], color[2]))
		return (smoothen(color, rss, w));
	return (average_supersampled_color(color));
}

void	render_scene(t_wrapper *w)
{
	int	*edge_color;
	int	last[3];
	int	color;
	int	n;

	edge_color = secure_malloc((w->data.xres + 2) * sizeof(int));
	n = w->data.yres / NUM_THREADS;
	w->j = n * w->tid;
	while (w->j < (n * (w->tid + 1)))
	{
		w->i = 0;
		while (w->i < w->data.xres)
		{
			color = calc_pixel_color(edge_color, last, w);
			w->mlx.cam->px_img[w->j * w->data.xres + w->i] = color;
			w->i++;
		}
		w->j++;
	}
}

static int	check_extension(char *arg, int i)
{
	while (arg[i])
		i++;
	if (i > 3 && arg[i - 1] == 't' && arg[i - 2] == 'r' && arg[i - 3] == '.')
		return (0);
	return (1);
}

int	main(int ac, char **av)
{
	t_wrapper	wrapper[NUM_THREADS];
	t_minilibx	mlx;
	t_scene		data;
	t_figures	*lst;

	if (ac != 2 || check_extension(av[1], 0))
		usage(av[0]);
	parse_scene(&mlx, &data, &lst, av);
	init_mlx(&mlx, &data);
	wrapp_data(mlx, data, lst, wrapper);
	multithreaded_render(wrapper);
	success_message(ac);
	graphic_loop(mlx, data);
	return (0);
}
