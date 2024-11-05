#include "minirt.h"

static int compute_first_corner(int *initial_colors, int center_color, t_rss sampling_info, t_wrapper *wrapper) {
    t_rss refined_sampling;
    int *corner_samples;
    int final_color;

    corner_samples = (int *)secure_malloc(sizeof(int) * 4);
    corner_samples[0] = initial_colors[0];
    corner_samples[1] = compute_ray(1, sampling_info, wrapper);
    corner_samples[2] = compute_ray(3, sampling_info, wrapper);
    corner_samples[3] = center_color;
    refined_sampling.limit = sampling_info.limit - 1;
    refined_sampling.i = sampling_info.i * 2 - 1;
    refined_sampling.j = sampling_info.j * 2 - 1;
    refined_sampling.xres = sampling_info.xres * 2;
    refined_sampling.yres = sampling_info.yres * 2;
    final_color = smoothen(corner_samples, refined_sampling, wrapper);
    return final_color;
}

static int compute_second_corner(int *initial_colors, int center_color, t_rss sampling_info, t_wrapper *wrapper) {
    t_rss refined_sampling;
    int *corner_samples;
    int final_color;

    corner_samples = (int *)secure_malloc(sizeof(int) * 4);
    corner_samples[0] = compute_ray(3, sampling_info, wrapper);
    corner_samples[1] = initial_colors[1];
    corner_samples[2] = center_color;
    corner_samples[3] = compute_ray(5, sampling_info, wrapper);
    refined_sampling.limit = sampling_info.limit - 1;
    refined_sampling.i = sampling_info.i * 2;
    refined_sampling.j = sampling_info.j * 2 - 1;
    refined_sampling.xres = sampling_info.xres * 2;
    refined_sampling.yres = sampling_info.yres * 2;
    final_color = smoothen(corner_samples, refined_sampling, wrapper);
    return final_color;
}

static int compute_third_corner(int *initial_colors, int center_color, t_rss sampling_info, t_wrapper *wrapper) {
    t_rss refined_sampling;
    int *corner_samples;
    int final_color;

    corner_samples = (int *)secure_malloc(sizeof(int) * 4);
    corner_samples[0] = compute_ray(3, sampling_info, wrapper);
    corner_samples[1] = center_color;
    corner_samples[2] = initial_colors[2];
    corner_samples[3] = compute_ray(7, sampling_info, wrapper);
    refined_sampling.limit = sampling_info.limit - 1;
    refined_sampling.i = sampling_info.i * 2 - 1;
    refined_sampling.j = sampling_info.j * 2;
    refined_sampling.xres = sampling_info.xres * 2;
    refined_sampling.yres = sampling_info.yres * 2;
    final_color = smoothen(corner_samples, refined_sampling, wrapper);
    return final_color;
}

static int compute_fourth_corner(int *initial_colors, int center_color, t_rss sampling_info, t_wrapper *wrapper) {
    t_rss refined_sampling;
    int *corner_samples;
    int final_color;

    corner_samples = (int *)secure_malloc(sizeof(int) * 4);
    corner_samples[0] = center_color;
    corner_samples[1] = compute_ray(5, sampling_info, wrapper);
    corner_samples[2] = compute_ray(7, sampling_info, wrapper);
    corner_samples[3] = initial_colors[3];
    refined_sampling.limit = sampling_info.limit - 1;
    refined_sampling.i = sampling_info.i * 2;
    refined_sampling.j = sampling_info.j * 2;
    refined_sampling.xres = sampling_info.xres * 2;
    refined_sampling.yres = sampling_info.yres * 2;
    final_color = smoothen(corner_samples, refined_sampling, wrapper);
    return final_color;
}

int smoothen(int *initial_colors, t_rss sampling_info, t_wrapper *wrapper) {
    int center_color;
    int corner_index;

    center_color = compute_ray(4, sampling_info, wrapper);
    for (corner_index = 0; corner_index < 4; corner_index++) {
        if (!calculate_color_difference(initial_colors[corner_index], center_color) || sampling_info.limit == 0) {
            initial_colors[corner_index] = average(initial_colors[corner_index], center_color);
        } else {
            if (corner_index == 0) {
                initial_colors[0] = compute_first_corner(initial_colors, center_color, sampling_info, wrapper);
            } else if (corner_index == 1) {
                initial_colors[1] = compute_second_corner(initial_colors, center_color, sampling_info, wrapper);
            } else if (corner_index == 2) {
                initial_colors[2] = compute_third_corner(initial_colors, center_color, sampling_info, wrapper);
            } else {
                initial_colors[3] = compute_fourth_corner(initial_colors, center_color, sampling_info, wrapper);
            }
        }
    }
    return average_supersampled_color(initial_colors);
}

