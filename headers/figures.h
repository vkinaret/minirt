/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   figures.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinaret <vkinaret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 20:41:09 by vkinaret          #+#    #+#             */
/*   Updated: 2024/11/07 20:56:05 by vkinaret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIGURES_H
# define FIGURES_H

# include "minirt.h"

typedef struct s_sphere
{
	t_p3	c;
	double	r;
}				t_sphere;

typedef struct s_plane
{
	t_p3	p;
}				t_plane;

typedef struct s_cylinder
{
	t_p3	c;
	t_p3	nv;
	double	r;
	double	h;
	double	dist1;
	double	dist2;
}				t_cylinder;

union			u_figures
{
	t_sphere	sp;
	t_plane		pl;
	t_cylinder	cy;
};

#endif
