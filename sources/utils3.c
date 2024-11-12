/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinaret <vkinaret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 20:06:31 by stuna             #+#    #+#             */
/*   Updated: 2024/11/12 14:50:23 by vkinaret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#ifndef LINUX

int	mlx_get_screen_size(void *mlx_ptr, int *sizex, int *sizey)
{
	mlx_ptr = (int *) mlx_ptr;
	sizex = sizey;
	return (0);
}
#endif

int	close_program(void *param)
{
	param = (void *)param;
	exit(EXIT_SUCCESS);
	return (1);
}

int	close_window(int keycode, t_minilibx *mlx)
{
	if (keycode == ESC_KEY)
		exit(0);
	else
	{
		mlx->cam = mlx->begin;
		mlx_put_image_to_window(
			mlx->mlx_ptr, mlx->win_ptr, mlx->cam->img_ptr, 0, 0);
	}
	return (1);
}

void	graphic_loop(t_minilibx mlx, t_scene data)
{
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, data.xres, data.yres, "miniRT");
	mlx_put_image_to_window(mlx.mlx_ptr, mlx.win_ptr, mlx.cam->img_ptr, 0, 0);
	mlx_hook(mlx.win_ptr, DESTROYNOTIFY, STRUCTURENOTIFYMASK, close_program, 0);
	mlx_hook(mlx.win_ptr, KEYPRESS, KEYPRESSMASK, close_window, &mlx);
	mlx_loop(mlx.mlx_ptr);
}
