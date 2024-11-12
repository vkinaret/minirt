/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distribute_pixels.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stuna <stuna@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:37:41 by stuna             #+#    #+#             */
/*   Updated: 2024/11/11 17:59:09 by stuna            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	*compute_first_column_sample(int *edge_colors,
		int last_colors[2], t_rss sampling_info, t_wrapper *wrapper)
{
	int	*sampled_colors;

	sampled_colors = (int *)secure_malloc(sizeof(int) * 4);
	if (sampling_info.j == wrapper->data.yres / NUM_THREADS * wrapper->tid)
	{
		sampled_colors[0] = compute_ray(0, sampling_info, wrapper);
		sampled_colors[1] = compute_ray(2, sampling_info, wrapper);
		sampled_colors[2] = compute_ray(6, sampling_info, wrapper);
		sampled_colors[3] = compute_ray(8, sampling_info, wrapper);
		last_colors[0] = sampled_colors[3];
		last_colors[1] = sampled_colors[1];
		edge_colors[0] = sampled_colors[2];
	}
	else
	{
		sampled_colors[0] = edge_colors[0];
		sampled_colors[1] = edge_colors[1];
		sampled_colors[2] = compute_ray(6, sampling_info, wrapper);
		sampled_colors[3] = compute_ray(8, sampling_info, wrapper);
		last_colors[0] = sampled_colors[3];
		edge_colors[0] = sampled_colors[2];
	}
	return (sampled_colors);
}

static int	*compute_last_column_sample(int *edge_colors,
		int last_colors[2], t_rss sampling_info, t_wrapper *wrapper)
{
	int	*sampled_colors;

	sampled_colors = (int *)secure_malloc(sizeof(int) * 4);
	if (sampling_info.j == wrapper->data.yres / NUM_THREADS * wrapper->tid)
	{
		sampled_colors[0] = last_colors[1];
		sampled_colors[1] = compute_ray(2, sampling_info, wrapper);
		sampled_colors[2] = last_colors[0];
		sampled_colors[3] = compute_ray(8, sampling_info, wrapper);
		edge_colors[sampling_info.i] = sampled_colors[2];
		edge_colors[sampling_info.i + 1] = sampled_colors[3];
	}
	else
	{
		sampled_colors[0] = edge_colors[sampling_info.i];
		sampled_colors[1] = edge_colors[sampling_info.i + 1];
		sampled_colors[2] = last_colors[0];
		sampled_colors[3] = compute_ray(3, sampling_info, wrapper);
		edge_colors[sampling_info.i] = sampled_colors[2];
		edge_colors[sampling_info.i + 1] = sampled_colors[3];
	}
	return (sampled_colors);
}

static int	*compute_center_pixel_sample(int *edge_colors,
		int last_colors[2], t_rss sampling_info, t_wrapper *wrapper)
{
	int	*sampled_colors;

	sampled_colors = (int *)secure_malloc(sizeof(int) * 4);
	if (sampling_info.j == wrapper->data.yres / NUM_THREADS * wrapper->tid)
	{
		sampled_colors[0] = last_colors[1];
		sampled_colors[1] = compute_ray(2, sampling_info, wrapper);
		sampled_colors[2] = last_colors[0];
		sampled_colors[3] = compute_ray(8, sampling_info, wrapper);
		last_colors[0] = sampled_colors[3];
		last_colors[1] = sampled_colors[1];
		edge_colors[sampling_info.i] = sampled_colors[2];
	}
	else
	{
		sampled_colors[0] = edge_colors[sampling_info.i];
		sampled_colors[1] = edge_colors[sampling_info.i + 1];
		sampled_colors[2] = last_colors[0];
		sampled_colors[3] = compute_ray(4, sampling_info, wrapper);
		last_colors[0] = sampled_colors[3];
		edge_colors[sampling_info.i] = sampled_colors[2];
	}
	return (sampled_colors);
}

int	*compute_pixel_sample(int *edge_colors, int last_colors[2],
		t_rss sampling_info, t_wrapper *wrapper)
{
	int	*sampled_colors;

	if (sampling_info.i == 0)
		sampled_colors = compute_first_column_sample(edge_colors,
				last_colors, sampling_info, wrapper);
	else if (sampling_info.i == wrapper->data.xres - 1)
		sampled_colors = compute_last_column_sample(edge_colors,
				last_colors, sampling_info, wrapper);
	else
		sampled_colors = compute_center_pixel_sample(edge_colors,
				last_colors, sampling_info, wrapper);
	return (sampled_colors);
}
