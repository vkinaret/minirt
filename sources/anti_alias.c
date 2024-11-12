/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anti_alias.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stuna <stuna@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:41:26 by stuna             #+#    #+#             */
/*   Updated: 2024/11/08 17:34:55 by stuna            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	compute_cr1(int *init_c, int cntr_c, t_rss rss, t_wrapper *wrp)
{
	t_rss	rsmp;
	int		*crnr_smpl;
	int		final_colr;

	crnr_smpl = (int *)secure_malloc(sizeof(int) * 4);
	crnr_smpl[0] = init_c[0];
	crnr_smpl[1] = compute_ray(1, rss, wrp);
	crnr_smpl[2] = compute_ray(3, rss, wrp);
	crnr_smpl[3] = cntr_c;
	rsmp.limit = rss.limit - 1;
	rsmp.i = rss.i * 2 - 1;
	rsmp.j = rss.j * 2 - 1;
	rsmp.xres = rss.xres * 2;
	rsmp.yres = rss.yres * 2;
	final_colr = smoothen(crnr_smpl, rsmp, wrp);
	return (final_colr);
}

static int	compute_cr2(int *init_c, int cntr_c, t_rss rss, t_wrapper *wrp)
{
	t_rss	rsmp;
	int		*crnr_smpl;
	int		final_colr;

	crnr_smpl = (int *)secure_malloc(sizeof(int) * 4);
	crnr_smpl[0] = compute_ray(3, rss, wrp);
	crnr_smpl[1] = init_c[1];
	crnr_smpl[2] = cntr_c;
	crnr_smpl[3] = compute_ray(5, rss, wrp);
	rsmp.limit = rss.limit - 1;
	rsmp.i = rss.i * 2;
	rsmp.j = rss.j * 2 - 1;
	rsmp.xres = rss.xres * 2;
	rsmp.yres = rss.yres * 2;
	final_colr = smoothen(crnr_smpl, rsmp, wrp);
	return (final_colr);
}

static int	compute_cr3(int *init_c, int cntr_c, t_rss rss, t_wrapper *wrp)
{
	t_rss	rsmp;
	int		*crnr_smpl;
	int		final_colr;

	crnr_smpl = (int *)secure_malloc(sizeof(int) * 4);
	crnr_smpl[0] = compute_ray(3, rss, wrp);
	crnr_smpl[1] = cntr_c;
	crnr_smpl[2] = init_c[2];
	crnr_smpl[3] = compute_ray(7, rss, wrp);
	rsmp.limit = rss.limit - 1;
	rsmp.i = rss.i * 2 - 1;
	rsmp.j = rss.j * 2;
	rsmp.xres = rss.xres * 2;
	rsmp.yres = rss.yres * 2;
	final_colr = smoothen(crnr_smpl, rsmp, wrp);
	return (final_colr);
}

static int	compute_cr4(int *init_c, int cntr_c, t_rss rss, t_wrapper *wrp)
{
	t_rss	rsmp;
	int		*crnr_smpl;
	int		final_colr;

	crnr_smpl = (int *)secure_malloc(sizeof(int) * 4);
	crnr_smpl[0] = cntr_c;
	crnr_smpl[1] = compute_ray(5, rss, wrp);
	crnr_smpl[2] = compute_ray(7, rss, wrp);
	crnr_smpl[3] = init_c[3];
	rsmp.limit = rss.limit - 1;
	rsmp.i = rss.i * 2;
	rsmp.j = rss.j * 2;
	rsmp.xres = rss.xres * 2;
	rsmp.yres = rss.yres * 2;
	final_colr = smoothen(crnr_smpl, rsmp, wrp);
	return (final_colr);
}

int	smoothen(int *init_c, t_rss rss, t_wrapper *wrp)
{
	int	center_colr;
	int	crnr_idx;

	crnr_idx = 0;
	center_colr = compute_ray(4, rss, wrp);
	while (crnr_idx < 4)
	{
		if (!calculate_color_difference(init_c[crnr_idx], center_colr)
			|| rss.limit == 0)
			init_c[crnr_idx] = average(init_c[crnr_idx], center_colr);
		else
		{
			if (crnr_idx == 0)
				init_c[0] = compute_cr1(init_c, center_colr, rss, wrp);
			else if (crnr_idx == 1)
				init_c[1] = compute_cr2(init_c, center_colr, rss, wrp);
			else if (crnr_idx == 2)
				init_c[2] = compute_cr3(init_c, center_colr, rss, wrp);
			else
				init_c[3] = compute_cr4(init_c, center_colr, rss, wrp);
		}
		crnr_idx++;
	}
	return (average_supersampled_color(init_c));
}
