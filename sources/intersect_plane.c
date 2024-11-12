/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stuna <stuna@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:02:41 by stuna             #+#    #+#             */
/*   Updated: 2024/11/11 20:59:48 by stuna            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	plane_intersection(t_p3 o, t_p3 d, t_figures *lst)
{
	double	x;
	double	denom;

	denom = dot(lst->normal, d);
	if (denom == 0)
		return (INFINITY);
	x = (dot(lst->normal, vsubstract(lst->fig.pl.p, o))) / denom;
	if (x > 0)
		return (x);
	return (INFINITY);
}

double	solve_surface(t_p3 o, t_p3 d, t_p3 plane_p, t_p3 plane_nv)
{
	double	x;
	double	denom;

	denom = dot(plane_nv, d);
	if (denom == 0)
		return (INFINITY);
	x = (dot(plane_nv, vsubstract(plane_p, o))) / denom;
	if (x > 0)
		return (x);
	return (INFINITY);
}

t_p3	calc_cy_normal(double x2[2], t_p3 o, t_p3 d, t_figures *lst)
{
	double	dist;
	double	x;

	if ((lst->fig.cy.dist1 >= 0 && lst->fig.cy.dist1 <= lst->fig.cy.h
			&& x2[0] > EPSILON) && (lst->fig.cy.dist2 >= 0
			&& lst->fig.cy.dist2 <= lst->fig.cy.h && x2[1] > EPSILON))
	{
		if (x2[0] < x2[1])
			assign_dist_x(&dist, &x, lst->fig.cy.dist1, x2[0]);
		else
			assign_dist_x(&dist, &x, lst->fig.cy.dist2, x2[1]);
	}
	else if (lst->fig.cy.dist1 >= 0
		&& lst->fig.cy.dist1 <= lst->fig.cy.h && x2[0] > EPSILON)
		assign_dist_x(&dist, &x, lst->fig.cy.dist1, x2[0]);
	else
		assign_dist_x(&dist, &x, lst->fig.cy.dist2, x2[1]);
	x2[0] = x;
	return (normalize(vsubstract(vsubstract(scal_x_vec(x, d),
					scal_x_vec(dist, lst->fig.cy.nv)),
				vsubstract(lst->fig.cy.c, o))));
}

int	solve_cylinder(double x[2], t_p3 o, t_p3 d, t_figures *lst)
{
	t_p3	v;
	t_p3	u;
	double	a;
	double	b;
	double	c;

	v = scal_x_vec(dot(d, lst->fig.cy.nv), lst->fig.cy.nv);
	v = vsubstract(d, v);
	u = scal_x_vec(dot(vsubstract(o, lst->fig.cy.c),
				lst->fig.cy.nv), lst->fig.cy.nv);
	u = vsubstract(vsubstract(o, lst->fig.cy.c), u);
	a = dot(v, v);
	b = 2 * dot(v, u);
	c = dot(u, u) - pow(lst->fig.cy.r, 2);
	x[0] = (-b + sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);
	x[1] = (-b - sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);
	if ((x[0] != x[0] && x[1] != x[1]) || (x[0] < EPSILON && x[1] < EPSILON))
	{
		x[0] = INFINITY;
		x[1] = INFINITY;
		return (0);
	}
	return (1);
}
