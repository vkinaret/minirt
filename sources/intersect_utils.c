/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stuna <stuna@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 19:09:45 by stuna             #+#    #+#             */
/*   Updated: 2024/11/11 19:09:47 by stuna            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	assign_dist_x(double *dist, double *x,
		double dist_value, double x_value)
{
	*dist = dist_value;
	*x = x_value;
}
