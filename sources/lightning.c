/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lightning.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinaret <vkinaret@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 21:08:05 by vkinaret          #+#    #+#             */
/*   Updated: 2024/11/07 21:08:06 by vkinaret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#include "minirt.h"

void add_coeficient(t_p3 *rgb, double coef, int color) {
    unsigned int mask;

    mask = 255 << 16;
    rgb->x += coef * ((color & mask) >> 16) / 255.0;
    mask >>= 8;
    rgb->y += coef * ((color & mask) >> 8) / 255.0;
    mask >>= 8;
    rgb->z += coef * (color & mask) / 255.0;
}

double calc_specular(t_v3 ray, t_inter *inter, t_scene data, t_figures *lst) {
    (void)lst;
    double light = 0;
    t_p3 direction;
    t_p3 p_to_cam;

    direction = vsubstract(data.l->o, inter->p);
    p_to_cam = vsubstract(ray.o, inter->p);
    return light;
}

void compute_light(t_v3 ray, t_inter *inter, t_scene data, t_figures *lst) {
    double light;
    t_p3 rgb;
    t_p3 direction;

    light = 0.0;
    ft_memset(&rgb, 0, sizeof(t_p3));
    add_coeficient(&rgb, data.ambient_light, data.al_color);
    while (data.l) {
        direction = vsubstract(data.l->o, inter->p);
        if (is_lit(inter->p, direction, lst)
                && dot(inter->normal, direction) > 0) {
            light = data.l->br * vcos(inter->normal, direction);
            add_coeficient(&rgb, light, data.l->color);
        }
        if (lst->specular) {
            light = calc_specular(ray, inter, data, lst);
            add_coeficient(&rgb, light, data.l->color);
        }
        data.l = data.l->next;
    }
    inter->color = modulate_color_with_light(inter->color, rgb);
}

void calc_normal(t_p3 p, t_p3 d, t_p3 *normal, t_figures *l) {
    if (l->flag == SP) {
        *normal = normalize(vsubstract(p, l->fig.sp.c));
        if (vcos(d, *normal) > 0)
            *normal = scal_x_vec(-1, *normal);
    } else {
        *normal = vcos(d, l->normal) > 0 ? scal_x_vec(-1, l->normal)
                                          : l->normal;
    }
}

int is_lit(t_p3 o, t_p3 d, t_figures *lst) {
    double in;

    while (lst) {
        if (lst->flag == SP)
            in = sphere_intersection(o, d, lst);
        else if (lst->flag == PL)
            in = plane_intersection(o, d, lst);
        else if (lst->flag == CY)
            in = cylinder_intersection(o, d, lst);
        if (in > EPSILON && in < 1)
            return 0;
        lst = lst->next;
    }
    return 1;
}

