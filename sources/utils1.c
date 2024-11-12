/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stuna <stuna@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:54:25 by stuna             #+#    #+#             */
/*   Updated: 2024/11/11 20:17:51 by stuna            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	init_mlx_resolution(t_minilibx *mlx, t_scene *data)
{
	t_camera	*cam_begin;
	int			x_displayres;
	int			y_displayres;

	mlx->mlx_ptr = mlx_init();
	if (OS_NAME == 2)
	{
		mlx_get_screen_size(mlx->mlx_ptr, &x_displayres, &y_displayres);
		if (data->xres > x_displayres)
			data->xres = x_displayres;
		if (data->yres > y_displayres)
			data->yres = y_displayres;
	}
	cam_begin = mlx->cam;
	mlx->begin = mlx->cam;
	mlx->cam = cam_begin;
}

static void	init_mlx_cameras(t_minilibx *mlx, t_scene *data)
{
	t_camera	*cam_begin;

	cam_begin = mlx->cam;
	while (mlx->cam)
	{
		mlx->cam->img_ptr = mlx_new_image(mlx->mlx_ptr, data->xres, data->yres);
		mlx->cam->px_img = (int *)mlx_get_data_addr(mlx->cam->img_ptr,
				&mlx->cam->bits_per_pixel,
				&mlx->cam->size_line, &mlx->cam->endian);
		mlx->cam = mlx->cam->next;
	}
	mlx->cam = cam_begin;
}

void	init_mlx(t_minilibx *mlx, t_scene *data)
{
	init_mlx_resolution(mlx, data);
	init_mlx_cameras(mlx, data);
}

void	success_message(int ac)
{
	int		t;

	t = NUM_THREADS;
	if (ac == 2)
	{
		printf("\nWorking with %d threads, ", t);
		printf("\nPress ESC to close the program.\n");
		printf("If there are more than one camera, ");
		printf("press space to change the camera view\n\n");
	}
	else
		exit(EXIT_SUCCESS);
}
