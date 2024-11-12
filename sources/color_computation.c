/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_computation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stuna <stuna@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:15:20 by stuna             #+#    #+#             */
/*   Updated: 2024/11/11 17:55:53 by stuna            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	adjust_color_brightness(int color, double coefficient)
{
	int			mask;
	int			red;
	int			green;
	int			blue;

	mask = 255;
	red = coefficient * ((color & (mask << 16)) >> 16);
	green = coefficient * ((color & (mask << 8)) >> 8);
	blue = coefficient * (color & mask);
	if (red > 255)
		red = 255;
	if (green > 255)
		green = 255;
	if (blue > 255)
		blue = 255;
	return ((red << 16) | (green << 8) | blue);
}

int	add_colors(int color1, int color2)
{
	int			mask;
	int			red;
	int			green;
	int			blue;

	mask = 255;
	red = ((color1 & (mask << 16)) + (color2 & (mask << 16))) & (mask << 16);
	green = ((color1 & (mask << 8)) + (color2 & (mask << 8))) & (mask << 8);
	blue = ((color1 & mask) + (color2 & mask)) & mask;
	return (red | green | blue);
}

int	modulate_color_with_light(int color, t_p3 light_rgb)
{
	unsigned int	mask;
	unsigned int	red;
	unsigned int	green;
	unsigned int	blue;

	mask = 255 << 16;
	red = light_rgb.x * ((color & mask) >> 16);
	mask >>= 8;
	green = light_rgb.y * ((color & mask) >> 8);
	mask >>= 8;
	blue = light_rgb.z * (color & mask);
	if (red > 255)
		red = 255;
	if (green > 255)
		green = 255;
	if (blue > 255)
		blue = 255;
	return ((red << 16) | (green << 8) | blue);
}

int	calculate_color_difference(int color1, int color2)
{
	int			mask;
	int			color_distance_squared;
	int			red_diff[2];
	int			green_diff[2];
	int			blue_diff[2];

	mask = 255;
	red_diff[0] = (color1 & (mask << 16)) >> 16;
	green_diff[0] = (color1 & (mask << 8)) >> 8;
	blue_diff[0] = color1 & mask;
	red_diff[1] = (color2 & (mask << 16)) >> 16;
	green_diff[1] = (color2 & (mask << 8)) >> 8;
	blue_diff[1] = color2 & mask;
	color_distance_squared = pow((red_diff[1] - red_diff[0]), 2)
		+ pow((green_diff[1] - green_diff[0]), 2)
		+ pow((blue_diff[1] - blue_diff[0]), 2);
	return (color_distance_squared > 1000);
}
