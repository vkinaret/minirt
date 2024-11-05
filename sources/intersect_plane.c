#include "minirt.h"

double plane_intersection(t_p3 o, t_p3 d, t_figures *lst) {
    double x;
    double denom;
    
    denom = dot(lst->normal, d);
    if (denom == 0)
        return INFINITY;

    x = (dot(lst->normal, vsubstract(lst->fig.pl.p, o))) / denom;
    return (x > 0 ? x : INFINITY);
}

