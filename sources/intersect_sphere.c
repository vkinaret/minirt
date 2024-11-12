/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stuna <stuna@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:05:23 by stuna             #+#    #+#             */
/*   Updated: 2024/11/11 20:46:00 by stuna            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	solve_sphere(double x[2], t_p3 o, t_p3 d, t_figures *lst)
{
	double	disc;
	t_p3	oc;
	double	k[3];

	oc = vsubstract(o, lst->fig.sp.c);
	k[0] = dot(d, d);
	k[1] = 2 * dot(d, oc);
	k[2] = dot(oc, oc) - lst->fig.sp.r * lst->fig.sp.r;
	disc = k[1] * k[1] - (4 * k[0] * k[2]);
	if (disc < 0)
	{
		x[0] = INFINITY;
		x[1] = INFINITY;
		return ;
	}
	x[0] = (-k[1] + sqrt(disc)) / (2 * k[0]);
	x[1] = (-k[1] - sqrt(disc)) / (2 * k[0]);
}

static double	get_closest_intersection(double *x)
{
	double	closest;

	closest = INFINITY;
	if (x[0] > EPSILON && x[0] < INFINITY)
		closest = x[0];
	if (x[1] > EPSILON && x[1] < INFINITY)
	{
		if (x[1] < closest)
			closest = x[1];
	}
	return (closest);
}

static double	check_surface(double *x, t_p3 o, t_p3 d, t_figures *lst)
{
	t_p3	ip1;
	t_p3	ip2;

	ip1 = vadd(o, scal_x_vec(x[0], d));
	ip2 = vadd(o, scal_x_vec(x[1], d));
	if (ip1.y >= lst->fig.sp.c.y && ip2.y >= lst->fig.sp.c.y)
	{
		if (x[0] < x[1])
			return (x[0]);
		else
			return (x[1]);
	}
	else if (ip1.y >= lst->fig.sp.c.y)
		return (x[0]);
	else if (ip2.y >= lst->fig.sp.c.y)
		return (x[1]);
	return (INFINITY);
}

double	sphere_intersection(t_p3 o, t_p3 d, t_figures *lst)
{
	double	x[2];
	double	closest;

	solve_sphere(x, o, d, lst);
	closest = get_closest_intersection(x);
	if (lst->surface != 4)
		return (closest);
	return (check_surface(x, o, d, lst));
}
