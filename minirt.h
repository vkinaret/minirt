#ifndef RENDER_H
#define RENDER_H

#include "MLX42/include/MLX42/MLX42.h"
#include <stdint.h>

// Function to calculate the color of a point on the sphere under lighting
uint32_t calculate_lighting(float x, float y, float z, uint32_t sphere_color, int light_x, int light_y, int light_z);

// Function to render a 3D sphere
void render_sphere(mlx_image_t* img, uint32_t sphere_color, int light_x, int light_y, int light_z, float aspect_ratio, float fov);

// Function to render a 3D cylinder
void render_cylinder(mlx_image_t* img, uint32_t cylinder_color, int light_x, int light_y, int light_z, float aspect_ratio, float fov);

#endif // RENDER_H
