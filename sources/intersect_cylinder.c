/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stuna <stuna@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:56:34 by stuna             #+#    #+#             */
/*   Updated: 2024/11/11 21:02:57 by stuna            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static double	cy_intersection(t_p3 o, t_p3 d, t_p3 *normal, t_figures *lst)
{
	double	x2[2];

	if (solve_cylinder(x2, o, d, lst) == 0)
		return (INFINITY);
	lst->fig.cy.dist1 = dot(lst->fig.cy.nv, vsubstract(scal_x_vec(x2[0], d),
				vsubstract(lst->fig.cy.c, o)));
	lst->fig.cy.dist2 = dot(lst->fig.cy.nv, vsubstract(scal_x_vec(x2[1], d),
				vsubstract(lst->fig.cy.c, o)));
	if (!((lst->fig.cy.dist1 >= 0 && lst->fig.cy.dist1 <= lst->fig.cy.h
				&& x2[0] > EPSILON) || (lst->fig.cy.dist2 >= 0
				&& lst->fig.cy.dist2 <= lst->fig.cy.h && x2[0] > EPSILON)))
		return (INFINITY);
	*normal = calc_cy_normal(x2, o, d, lst);
	return (x2[0]);
}

static void	compute_intersection_points(t_p3 o, t_p3 d,
		t_figures *lst, t_intersection *intersections)
{
	t_p3	c2;

	c2 = vadd(lst->fig.cy.c, scal_x_vec(lst->fig.cy.h, lst->fig.cy.nv));
	intersections->id1 = solve_surface(o, d, lst->fig.cy.c, lst->fig.cy.nv);
	intersections->id2 = solve_surface(o, d, c2, lst->fig.cy.nv);
	intersections->ip1 = vadd(o, scal_x_vec(intersections->id1, d));
	intersections->ip2 = vadd(o, scal_x_vec(intersections->id2, d));
}

static double	validate_and_select_intersection(t_intersection *intersections,
		t_figures *lst)
{
	t_p3	c2;

	c2 = vadd(lst->fig.cy.c, scal_x_vec(lst->fig.cy.h, lst->fig.cy.nv));
	if ((intersections->id1 < INFINITY
			&& distance(intersections->ip1, lst->fig.cy.c)
			<= lst->fig.cy.r) && (intersections->id2 < INFINITY
			&& distance(intersections->ip2, c2) <= lst->fig.cy.r))
	{
		if (intersections->id1 < intersections->id2)
			return (intersections->id1);
		return (intersections->id2);
	}
	else if (intersections->id1 < INFINITY
		&& distance(intersections->ip1, lst->fig.cy.c) <= lst->fig.cy.r)
		return (intersections->id1);
	else if (intersections->id2 < INFINITY
		&& distance(intersections->ip2, c2) <= lst->fig.cy.r)
		return (intersections->id2);
	return (INFINITY);
}

static double	caps_intersection(t_p3 o, t_p3 d, t_figures *lst)
{
	t_intersection	intersections;

	compute_intersection_points(o, d, lst, &intersections);
	return (validate_and_select_intersection(&intersections, lst));
}

double	cylinder_intersection(t_p3 o, t_p3 d, t_figures *lst)
{
	double	cylinder_inter;
	double	caps_inter;
	t_p3	cy_normal;

	cylinder_inter = cy_intersection(o, d, &cy_normal, lst);
	caps_inter = caps_intersection(o, d, lst);
	if (cylinder_inter < INFINITY || caps_inter < INFINITY)
	{
		if (cylinder_inter < caps_inter)
		{
			lst->normal = cy_normal;
			return (cylinder_inter);
		}
		lst->normal = lst->fig.cy.nv;
		return (caps_inter);
	}
	return (INFINITY);
}
