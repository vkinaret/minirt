/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinaret <vkinaret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:51:02 by vkinaret          #+#    #+#             */
/*   Updated: 2024/11/12 16:33:28 by vkinaret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_p3	parse_p3(char **str)
{
	t_p3	p;

	p.x = stof(str);
	comma(str);
	p.y = stof(str);
	comma(str);
	p.z = stof(str);
	next(str);
	return (p);
}

int	parse_color(char **str)
{
	int	r;
	int	g;
	int	b;

	r = 0;
	g = 0;
	b = 0;
	r |= stoi(str);
	in_range(r, 0, 255, "colors must be in range [0, 255],");
	r <<= 16;
	comma(str);
	g |= stoi(str);
	in_range(g, 0, 255, "colors must be in range [0, 255],");
	g <<= 8;
	comma(str);
	b |= stoi(str);
	in_range(b, 0, 255, "colors must be in range [0, 255],");
	return (r | g | b);
}
