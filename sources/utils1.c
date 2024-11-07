/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinaret <vkinaret@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 21:06:02 by vkinaret          #+#    #+#             */
/*   Updated: 2024/11/07 21:06:04 by vkinaret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int			close_program(void *param)
{
	param = (void *)param;
	exit(EXIT_SUCCESS);
	return (1);
}

int			next_cam(int keycode, t_minilibx *mlx)
{
	if (keycode == ESC_KEY)
		exit(0);
	if (keycode != SP_KEY)
		return (0);
	if (mlx->cam->next)
	{
		mlx->cam = mlx->cam->next;
		mlx_put_image_to_window(
				mlx->mlx_ptr, mlx->win_ptr, mlx->cam->img_ptr, 0, 0);
	}
	else
	{
		mlx->cam = mlx->begin;
		mlx_put_image_to_window(
				mlx->mlx_ptr, mlx->win_ptr, mlx->cam->img_ptr, 0, 0);
	}
	return (1);
}

void		init_mlx(t_minilibx *mlx, t_scene *data)
{
	t_camera	*cam_begin;
	int			x_displayres;
	int			y_displayres;

	mlx->mlx_ptr = mlx_init();
	if (OS_NAME == 2)
	{
		mlx_get_screen_size(mlx->mlx_ptr, &x_displayres, &y_displayres);
		data->xres = data->xres < x_displayres ? data->xres : x_displayres;
		data->yres = data->yres < y_displayres ? data->yres : y_displayres;
	}
	cam_begin = mlx->cam;
	mlx->begin = mlx->cam;
	while (mlx->cam)
	{
		mlx->cam->img_ptr = mlx_new_image(mlx->mlx_ptr, data->xres, data->yres);
		mlx->cam->px_img = (int *)mlx_get_data_addr(mlx->cam->img_ptr,
			&mlx->cam->bits_per_pixel, &mlx->cam->size_line, &mlx->cam->endian);
		mlx->cam = mlx->cam->next;
	}
	mlx->cam = cam_begin;
}

void		success_message(int ac)
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

void		graphic_loop(t_minilibx mlx, t_scene data)
{
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, data.xres, data.yres,
															"miniRT");
	mlx_put_image_to_window(mlx.mlx_ptr, mlx.win_ptr, mlx.cam->img_ptr, 0, 0);
	mlx_hook(mlx.win_ptr, DESTROYNOTIFY, STRUCTURENOTIFYMASK, close_program, 0);
	mlx_hook(mlx.win_ptr, KEYPRESS, KEYPRESSMASK, next_cam, &mlx);
	mlx_loop(mlx.mlx_ptr);
}
