/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinaret <vkinaret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 17:12:09 by vkinaret          #+#    #+#             */
/*   Updated: 2024/11/12 17:12:20 by vkinaret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_sphere(t_figures **elem, char *str)
{
	t_figures	*lst;

	ft_addnewlst_back(elem);
	lst = *elem;
	while (lst->next)
		lst = lst->next;
	lst->flag = SP;
	next(&str);
	lst->fig.sp.c = parse_p3(&str);
	lst->fig.sp.r = stof(&str) / 2;
	in_range(lst->fig.sp.r, 0, INFINITY, "sphere");
	lst->color = parse_color(&str);
}

void	parse_plane(t_figures **elem, char *str)
{
	t_figures	*lst;

	ft_addnewlst_back(elem);
	lst = *elem;
	while (lst->next)
		lst = lst->next;
	lst->flag = PL;
	next(&str);
	lst->fig.pl.p = parse_p3(&str);
	lst->normal = parse_p3(&str);
	in_range(lst->normal.x, -1, 1, "plane normal vector x");
	in_range(lst->normal.y, -1, 1, "plane normal vector y");
	in_range(lst->normal.z, -1, 1, "plane normal vector z");
	lst->normal = normalize(lst->normal);
	lst->color = parse_color(&str);
}

void	parse_cylinder(t_figures **elem, char *str)
{
	t_figures	*lst;

	ft_addnewlst_back(elem);
	lst = *elem;
	while (lst->next)
		lst = lst->next;
	lst->flag = CY;
	next(&str);
	lst->fig.cy.c = parse_p3(&str);
	lst->fig.cy.nv = parse_p3(&str);
	in_range(lst->fig.cy.nv.x, -1, 1, "cy normal vector x");
	in_range(lst->fig.cy.nv.y, -1, 1, "cy normal vector y");
	in_range(lst->fig.cy.nv.z, -1, 1, "cy normal vector z");
	lst->fig.cy.nv = normalize(lst->fig.cy.nv);
	lst->fig.cy.r = stof(&str) / 2;
	in_range(lst->fig.cy.r, 0, INFINITY, "cylinder");
	lst->fig.cy.h = stof(&str);
	in_range(lst->fig.cy.h, 0, INFINITY, "cylinder");
	lst->color = parse_color(&str);
}
