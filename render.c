/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinaret <vkinaret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 19:38:34 by vkinaret          #+#    #+#             */
/*   Updated: 2024/08/26 16:52:35 by vkinaret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

uint32_t calculate_lighting(float x, float y, float z, uint32_t sphere_color, int light_x, int light_y, int light_z, double brightness) 
{
    // Calculate the normal vector at the point
    float nx = x;
    float ny = y;
    float nz = z;

    // Normalize the normal vector
    float length = sqrt(nx * nx + ny * ny + nz * nz);
    nx /= length;
    ny /= length;
    nz /= length;

    // Calculate the light direction vector
    float lx = light_x - x;
    float ly = light_y - y;
    float lz = light_z - z;

    // Normalize the light direction vector
    length = sqrt(lx * lx + ly * ly + lz * lz);
    lx /= length;
    ly /= length;
    lz /= length;

    // Calculate the dot product of the normal and light direction vectors
    float dot = nx * lx + ny * ly + nz * lz;

    // Clamp the dot product to the range [0, 1]
    if (dot < 0) dot = 0;

    // Extract the RGB components of the sphere color
    t_int r = (sphere_color >> 8) & 0xFF;
    t_int g = (sphere_color >> 16) & 0xFF;
    t_int b = (sphere_color >> 0) & 0xFF;

    // Calculate the ambient component
    float ambient_r = r * brightness * REFLECT;
    float ambient_g = g * brightness * REFLECT;
    float ambient_b = b * brightness * REFLECT;

    // Apply the direct lighting to each component
    r = (uint8_t)fminf(ambient_r + (r * dot), 255);
    g = (uint8_t)fminf(ambient_g + (g * dot), 255);
    b = (uint8_t)fminf(ambient_b + (b * dot), 255);

    // Combine the components back into a single color
    return (r << 16) | (g << 8) | b;
}

// Helper function to normalize a vector
void normalize(float* x, float* y, float* z) {
    float length = sqrt((*x) * (*x) + (*y) * (*y) + (*z) * (*z));
    if (length != 0.0) {
        *x /= length;
        *y /= length;
        *z /= length;
    }
}

// Function to render a 3D sphere
void render_sphere(t_object *sphere, t_scene *scene, int light_x, int light_y, int light_z, float camera_x, float camera_y, float camera_z) {
    float sphere_radius = 180.0;
    int sphere_center_x = 400;
    int sphere_center_y = 300;
    float camera_distance = 500; // Distance from camera to the projection plane

    // Define smaller step sizes for phi and theta to make the sphere denser
    float step_phi = 0.005;
    float step_theta = 0.005;

    // Compute the normalized camera direction vector
    float camera_direction_x = camera_x;
    float camera_direction_y = camera_y;
    float camera_direction_z = camera_z;
    normalize(&camera_direction_x, &camera_direction_y, &camera_direction_z);

    // Convert FOV from degrees to radians
    float fov_radians = scene->camera->fov * (PI / 180.0);

    // Calculate the perspective projection scaling factors
    float scale_x = tan(fov_radians / 2.0) * ASPECT;
    float scale_y = tan(fov_radians / 2.0);

    for (float phi = 0; phi < PI; phi += step_phi) {
        for (float theta = 0; theta < 2 * PI; theta += step_theta) {
            float x = sphere_radius * sin(phi) * cos(theta);
            float y = sphere_radius * sin(phi) * sin(theta);
            float z = sphere_radius * cos(phi);

            // Apply camera transformation
            float transformed_x = x - camera_x;
            float transformed_y = y - camera_y;
            float transformed_z = z - camera_z;

            // Compute projected coordinates
            float projected_x = (transformed_x * scale_x * camera_distance) / (camera_distance + transformed_z) + sphere_center_x;
            float projected_y = (transformed_y * scale_y * camera_distance) / (camera_distance + transformed_z) + sphere_center_y;

            // Pass ambient light parameters to calculate_lighting
            uint32_t color = calculate_lighting(transformed_x, transformed_y, transformed_z, sphere->color.hex, light_x, light_y, light_z, scene->ambient->ratio);

            if (projected_x >= 0 && projected_x < scene->img->width && projected_y >= 0 && projected_y < scene->img->height) {
                mlx_put_pixel(scene->img, (int)projected_x, (int)projected_y, color);
            }
        }
    }
}

// Function to render a 3D cylinder with new POV logic
void render_cylinder(t_object *cylinder, t_scene *scene, int light_x, int light_y, int light_z, float camera_x, float camera_y, float camera_z) {
    float cylinder_radius = 100.0;
    float cylinder_height = 200.0;
    int cylinder_center_x = 450;
    int cylinder_center_y = 100;
    float camera_distance = 500.0; // Distance from camera to the projection plane

    // Define smaller step sizes for theta and z to make the cylinder denser
    float step_theta = 0.005; // Adjusted for practicality
    float step_y = 0.005; // Adjusted for practicality

    // Compute the normalized camera direction vector
    float camera_direction_x = camera_x;
    float camera_direction_y = camera_y;
    float camera_direction_z = camera_z;
    normalize(&camera_direction_x, &camera_direction_y, &camera_direction_z);

    // Convert FOV from degrees to radians
    float fov_radians = scene->camera->fov * (PI / 180.0);

    // Calculate the perspective projection scaling factors
    float scale_x = tan(fov_radians / 2.0) * ASPECT;
    float scale_z = tan(fov_radians / 2.0);

    // Render the cylinder using cylindrical coordinates
    for (float theta = 0; theta < 2 * PI; theta += step_theta) {
        for (float y = -cylinder_height / 2; y < cylinder_height / 2; y += step_y) {
            float x = cylinder_radius * cos(theta);
            float z = cylinder_radius * sin(theta);

            // Apply camera transformation
            float transformed_x = x - camera_x;
            float transformed_y = y - camera_y;
            float transformed_z = z - camera_z;

            // Compute projected coordinates
            float projected_x = (transformed_x * scale_x * camera_distance) / (camera_distance + transformed_z) + cylinder_center_x;
            float projected_y = (transformed_y * scale_z * camera_distance) / (camera_distance + transformed_z) + cylinder_center_y;

            // Pass ambient light parameters to calculate_lighting
            uint32_t color = calculate_lighting(transformed_x, transformed_y, transformed_z, cylinder->color.hex, light_x, light_y, light_z, scene->ambient->ratio);

            if (projected_x >= 0 && projected_x < scene->img->width && projected_y >= 0 && projected_y < scene->img->height) {
                mlx_put_pixel(scene->img, (int)projected_x, (int)projected_y, color);
            }
        }
    }
}

// Function to render a solid 3D cube with colorful faces and lighting
void render_plane(t_object *plane, t_scene *scene, int light_x, int light_y, int light_z, float camera_x, float camera_y, float camera_z) {
    float cube_width = scene->img->width * 3; // Width (X dimension)
    float cube_height = 1.0; // Height (Y dimension) - Adjust this value as needed
    float cube_depth = 500.0; // Depth (Z dimension)
    int cube_center_x = scene->img->width; // Center horizontally
    int cube_center_y = scene->img->height / 3; // Center vertically
    float camera_distance = 400.0; // Distance from camera to the projection plane

    if (plane->id == 'P')
        printf("42\n");

    // Convert FOV from degrees to radians
    float fov_radians = scene->camera->fov * (PI / 180.0);

    // Calculate the perspective projection scaling factors
    float scale_x = tan(fov_radians / 2.0) * ASPECT;
    float scale_y = tan(fov_radians / 2.0);

    // Render each voxel (pixel) within the cube
    for (float x = -cube_width; x < cube_width; ++x) {
        for (float y = -cube_height; y < cube_height; ++y) {
            for (float z = -cube_depth; z < cube_depth; ++z) {
                // Apply camera transformation
                float transformed_x = x - camera_x;
                float transformed_y = y - camera_y;
                float transformed_z = z - camera_z;

                // Compute projected coordinates
                float projected_x = (transformed_x * scale_x * camera_distance) / (camera_distance + transformed_z) + cube_center_x;
                float projected_y = (transformed_y * scale_y * camera_distance) / (camera_distance + transformed_z) + cube_center_y;

                if (projected_x >= 0 && projected_x < scene->img->width && projected_y >= 0 && projected_y < scene->img->height) {
                    // Calculate ambient and diffuse lighting using the provided function
                    uint32_t color = calculate_lighting(transformed_x, transformed_y, transformed_z, plane->color.hex, light_x, light_y, light_z, scene->ambient->ratio);
                    mlx_put_pixel(scene->img, (int)projected_x, (int)projected_y, color);
                }
            }
        }
    }
}

void    render_objects(t_scene *scene)
{
    t_object    *object;
	int         light_x = -2500;
    int         light_y = -50;
    int         light_z = -100;
    float       camera_x = 0.0;
    float       camera_y = -200;
    float       camera_z = -300;
    
    object = scene->objects;
    while (object)
    {
        if (object->id == 'P')
            render_plane(object, scene, light_x, light_y, light_z, camera_x, camera_y, camera_z);
        else if (object->id == 'S')
            render_sphere(object, scene, light_x, light_y, light_z, camera_x, camera_y, camera_z);
        else if (object->id == 'C')
            render_cylinder(object, scene, light_x, light_y, light_z, camera_x, camera_y, camera_z);
        object = object->next;
    }
}
