#include "render.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>

#define PI 3.14159265

// Function to calculate the color of a point on the sphere under lighting
uint32_t calculate_lighting(float x, float y, float z, uint32_t sphere_color, int light_x, int light_y, int light_z) {
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
    if (dot > 1) dot = 1;

    // Extract the RGB components of the sphere color
    uint8_t r = (sphere_color >> 16) & 0xFF;
    uint8_t g = (sphere_color >> 8) & 0xFF;
    uint8_t b = sphere_color & 0xFF;

    // Apply the lighting to each component
    r = (uint8_t)(r * dot);
    g = (uint8_t)(g * dot);
    b = (uint8_t)(b * dot);

    // Combine the components back into a single color
    return (r << 16) | (g << 8) | b;
}

// Function to render a 3D sphere
void render_sphere(mlx_image_t* img, uint32_t sphere_color, int light_x, int light_y, int light_z, float aspect_ratio, float fov) {
    float sphere_radius = 100.0;
    int sphere_center_x = 400;
    int sphere_center_y = 300;
    float camera_distance = 400.0; // Distance from camera to the projection plane

    // Define smaller step sizes for phi and theta to make the sphere denser
    float step_phi = 0.01;
    float step_theta = 0.01;

    // Convert FOV from degrees to radians
    float fov_radians = fov * (PI / 180.0);

    // Calculate the perspective projection scaling factors
    float scale_x = tan(fov_radians / 2.0) * aspect_ratio;
    float scale_y = tan(fov_radians / 2.0);

    // Render the sphere using spherical coordinates
    for (float phi = 0; phi < PI; phi += step_phi) {
        for (float theta = 0; theta < 2 * PI; theta += step_theta) {
            float x = sphere_radius * sin(phi) * cos(theta);
            float y = sphere_radius * sin(phi) * sin(theta);
            float z = sphere_radius * cos(phi);

            // Apply perspective projection with aspect ratio and FOV
            float projected_x = (x * scale_x * camera_distance) / (camera_distance + z) + sphere_center_x;
            float projected_y = (y * scale_y * camera_distance) / (camera_distance + z) + sphere_center_y;

            // Calculate the color of the point under the light
            uint32_t color = calculate_lighting(x, y, z, sphere_color, light_x, light_y, light_z);

            // Plot the point (projected_x, projected_y) on the image using mlx42
            if (projected_x >= 0 && projected_x < 800 && projected_y >= 0 && projected_y < 600) { // Ensure the point is within bounds
                mlx_put_pixel(img, (int)projected_x, (int)projected_y, color);
            }
        }
    }
}

// Function to render a 3D cylinder
void render_cylinder(mlx_image_t* img, uint32_t cylinder_color, int light_x, int light_y, int light_z, float aspect_ratio, float fov) {
    float cylinder_radius = 50.0;
    float cylinder_height = 200.0;
    int cylinder_center_x = 600;
    int cylinder_center_y = 300;
    float camera_distance = 400.0; // Distance from camera to the projection plane

    // Define smaller step sizes for theta and z to make the cylinder denser
    float step_theta = 0.01;
    float step_z = 1.0;

    // Convert FOV from degrees to radians
    float fov_radians = fov * (PI / 180.0);

    // Calculate the perspective projection scaling factors
    float scale_x = tan(fov_radians / 2.0) * aspect_ratio;
    float scale_y = tan(fov_radians / 2.0);

    // Renderthe cylinder using cylindrical coordinates
    for (float theta = 0; theta < 2 * PI; theta += step_theta) {
        for (float z = -cylinder_height / 2; z < cylinder_height / 2; z += step_z) {
            float x = cylinder_radius * cos(theta);
            float y = cylinder_radius * sin(theta);

            // Apply perspective projection with aspect ratio and FOV
            float projected_x = (x * scale_x * camera_distance) / (camera_distance + z) + cylinder_center_x;
            float projected_y = (y * scale_y * camera_distance) / (camera_distance + z) + cylinder_center_y;

            // Calculate the color of the point under the light
            uint32_t color = calculate_lighting(x, y, z, cylinder_color, light_x, light_y, light_z);

            // Plot the point (projected_x, projected_y) on the image using mlx42
            if (projected_x >= 0 && projected_x < 800 && projected_y >= 0 && projected_y < 600) { // Ensure the point is within bounds
                mlx_put_pixel(img, (int)projected_x, (int)projected_y, color);
            }
        }
    }
}
 
