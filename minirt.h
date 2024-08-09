#ifndef RENDER_H
#define RENDER_H

#include "MLX42/include/MLX42/MLX42.h"
#include <stdint.h>
#include <stdlib.h>
#include <math.h>


uint32_t calculate_lighting(float x, float y, float z, uint32_t sphere_color, int light_x, int light_y, int light_z, float ambient_intensity, float ambient_reflectivity);

// Function to render a 3D sphere
void render_sphere(mlx_image_t* img, uint32_t sphere_color, int light_x, int light_y, int light_z, float aspect_ratio, float fov,float ambient_intensity,float ambient_reflectivity,float camera_x, float camera_y, float camera_z);

// Function to render a 3D cylinder
void render_cylinder(mlx_image_t* img, uint32_t cylinder_color, int light_x, int light_y, int light_z, float aspect_ratio, float fov,float ambient_intensity,float ambient_reflectivity, float camera_x, float camera_y, float camera_z);




void render_plane(mlx_image_t* img, uint32_t plane_color, float aspect_ratio, float fov);






#endif // RENDER_H
