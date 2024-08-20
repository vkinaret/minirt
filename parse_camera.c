/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinaret <vkinaret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 00:10:46 by vkinaret          #+#    #+#             */
/*   Updated: 2024/08/20 21:30:20 by vkinaret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	parse_fov(char *line, int i)
{
	while (ft_isdigit(line[i]))
		i++;
	if (i == 0 || i > 3 || (i == 3 && ft_strncmp(line, "180", i) > 0))
		return (1);
	return (0);
}

int	parse_camera(char *line)
{
	while (*line == ' ')
		line++;
	if (parse_coordinates(line, 0, -1))
		return (print_error(COORDINATES, 13));
	while (ft_isdigit(*line) || *line == ',' || *line == '-' || *line == '.')
		line++;
	while (*line == ' ')
		line++;
	if (parse_vector(line, 0, -1))
		return (print_error(VECTOR, 14));
	while (ft_isdigit(*line) || *line == ',' || *line == '-' || *line == '.')
		line++;
	while (*line == ' ')
		line++;
	if (parse_fov(line, 0))
		return (print_error(FOV, 15));
	while (ft_isdigit(*line))
		line++;
	if (*line != '\n')
		return (print_error(NEWLINE, 16));
	return (0);
}
