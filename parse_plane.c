/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinaret <vkinaret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 03:17:30 by vkinaret          #+#    #+#             */
/*   Updated: 2024/08/28 14:50:45 by vkinaret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_plane(char *line)
{
	while (*line == ' ')
		line++;
	if (parse_coordinates(line, 0, -1))
		return (print_error(COORDINATES, 17));
	while (ft_isdigit(*line) || *line == ',' || *line == '-' || *line == '.')
		line++;
	while (*line == ' ')
		line++;
	if (parse_vector(line, 0, -1))
		return (print_error(VECTOR, 18));
	while (ft_isdigit(*line) || *line == ',' || *line == '-' || *line == '.')
		line++;
	while (*line == ' ')
		line++;
	if (parse_color(line, 0, 0) == 1)
		return (print_error(COLOR, 19));
	while (ft_isdigit(*line) || *line == ',')
		line++;
	if (*line != '\n')
		return (print_error(NEWLINE, 20));
	return (0);
}
