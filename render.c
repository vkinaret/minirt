#include "render.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>

#define PI 3.14159265358979323846

uint32_t calculate_lighting(float x, float y, float z, uint32_t sphere_color, int light_x, int light_y, int light_z, float ambient_intensity, float ambient_reflectivity) {
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
    uint8_t r = (sphere_color >> 16) & 0xFF;
    uint8_t g = (sphere_color >> 8) & 0xFF;
    uint8_t b = sphere_color & 0xFF;

    // Calculate the ambient component
    float ambient_r = r * ambient_intensity * ambient_reflectivity;
    float ambient_g = g * ambient_intensity * ambient_reflectivity;
    float ambient_b = b * ambient_intensity * ambient_reflectivity;

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
void render_sphere(mlx_image_t* img, uint32_t sphere_color, int light_x, int light_y, int light_z, float aspect_ratio, float fov, float ambient_intensity,float ambient_reflectivity,float camera_x, float camera_y, float camera_z) {
    float sphere_radius = 200.0;
    int sphere_center_x = 400;
    int sphere_center_y = 300;
    float camera_distance = 400; // Distance from camera to the projection plane

    // Define smaller step sizes for phi and theta to make the sphere denser
    float step_phi = 0.001;
    float step_theta = 0.001;

    // Compute the normalized camera direction vector
    float camera_direction_x = camera_x;
    float camera_direction_y = camera_y;
    float camera_direction_z = camera_z;
    normalize(&camera_direction_x, &camera_direction_y, &camera_direction_z);

    // Convert FOV from degrees to radians
    float fov_radians = fov * (PI / 180.0);

    // Calculate the perspective projection scaling factors
    float scale_x = tan(fov_radians / 2.0) * aspect_ratio;
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
            uint32_t color = calculate_lighting(transformed_x, transformed_y, transformed_z, sphere_color, light_x, light_y, light_z, ambient_intensity, ambient_reflectivity);

            if (projected_x >= 0 && projected_x < img->width && projected_y >= 0 && projected_y < img->height) {
                mlx_put_pixel(img, (int)projected_x, (int)projected_y, color);
            }
        }
    }
}
/*
// Function to render a 3D cylinder
void render_cylinder(mlx_image_t* img, uint32_t cylinder_color, int light_x, int light_y, int light_z, float aspect_ratio, float fov,float ambient_intensity,float ambient_reflectivity) {
    float cylinder_radius = 90.0;
    float cylinder_height = 200.0;
    int cylinder_center_x = 600;
    int cylinder_center_y = 200;
    float camera_distance = 700.0; // Distance from camera to the projection plane

    // Define smaller step sizes for theta and z to make the cylinder denser
    float step_theta = 0.005; // Adjusted for practicality
    float step_y = 0.005; // Adjusted for practicality

    // Convert FOV from degrees to radians
    float fov_radians = fov * (PI / 180.0);

    // Calculate the perspective projection scaling factors
    float scale_x = tan(fov_radians / 2.0) * aspect_ratio;
    float scale_z = tan(fov_radians / 2.0);

    // Render the cylinder using cylindrical coordinates
	for (float theta = 0; theta < 2 * PI; theta += step_theta) {
        for (float y = -cylinder_height / 2; y < cylinder_height / 2; y += step_y) {
            float x = cylinder_radius * cos(theta);
            float z = cylinder_radius * sin(theta);

            float projected_x = (x * scale_x * camera_distance) / (camera_distance + z) + cylinder_center_x;
            float projected_y = (y * scale_z * camera_distance) / (camera_distance + z) + cylinder_center_y;

            // Pass ambient light parameters to calculate_lighting
            uint32_t color = calculate_lighting(x, y, z, cylinder_color, light_x, light_y, light_z, ambient_intensity, ambient_reflectivity);

            if (projected_x >= 0 && projected_x < img->width && projected_y >= 0 && projected_y < img->height) {
                mlx_put_pixel(img, (int)projected_x, (int)projected_y, color);
			}
            
        }
    }
}*/



// Function to render a 3D cylinder with new POV logic
void render_cylinder(mlx_image_t* img, uint32_t cylinder_color, int light_x, int light_y, int light_z, float aspect_ratio, float fov, float ambient_intensity, float ambient_reflectivity, float camera_x, float camera_y, float camera_z) {
    float cylinder_radius = 90.0;
    float cylinder_height = 200.0;
    int cylinder_center_x = 600;
    int cylinder_center_y = 200;
    float camera_distance = 700.0; // Distance from camera to the projection plane

    // Define smaller step sizes for theta and z to make the cylinder denser
    float step_theta = 0.005; // Adjusted for practicality
    float step_y = 0.005; // Adjusted for practicality

    // Compute the normalized camera direction vector
    float camera_direction_x = camera_x;
    float camera_direction_y = camera_y;
    float camera_direction_z = camera_z;
    normalize(&camera_direction_x, &camera_direction_y, &camera_direction_z);

    // Convert FOV from degrees to radians
    float fov_radians = fov * (PI / 180.0);

    // Calculate the perspective projection scaling factors
    float scale_x = tan(fov_radians / 2.0) * aspect_ratio;
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
            uint32_t color = calculate_lighting(transformed_x, transformed_y, transformed_z, cylinder_color, light_x, light_y, light_z, ambient_intensity, ambient_reflectivity);

            if (projected_x >= 0 && projected_x < img->width && projected_y >= 0 && projected_y < img->height) {
                mlx_put_pixel(img, (int)projected_x, (int)projected_y, color);
            }
        }
    }
}


















// Helper function to swap two integers
static void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to draw a horizontal line between two x-coordinates
static void draw_line(mlx_image_t* img, int x1, int x2, int y, uint32_t color) {
    if (x1 > x2) {
        swap(&x1, &x2);
    }
    for (int x = x1; x <= x2; ++x) {
        mlx_put_pixel(img, x, y, color);
    }
}

static void draw_triangle(mlx_image_t* img, int x1, int y1, int x2, int y2, int x3, int y3, uint32_t color) {
    // Ensure vertices are ordered by y-coordinate
    if (y1 > y2) { swap(&x1, &x2); swap(&y1, &y2); }
    if (y1 > y3) { swap(&x1, &x3); swap(&y1, &y3); }
    if (y2 > y3) { swap(&x2, &x3); swap(&y2, &y3); }

    // Compute slopes of the triangle edges
    float slope1 = (y2 != y1) ? (float)(x2 - x1) / (y2 - y1) : 0;
    float slope2 = (y3 != y2) ? (float)(x3 - x2) / (y3 - y2) : 0;
    float slope3 = (y3 != y1) ? (float)(x3 - x1) / (y3 - y1) : 0;

    // Fill the triangle by scanlines
    for (int y = y1; y <= y3; ++y) {
        int x_left, x_right;

        if (y < y2) {
            x_left = x1 + (int)((y - y1) * slope3);
            x_right = x1 + (int)((y - y1) * slope1);
        } else {
            x_left = x2 + (int)((y - y2) * slope2);
            x_right = x1 + (int)((y - y1) * slope3);
        }

        if (x_left > x_right) {
            swap(&x_left, &x_right);
        }

        draw_line(img, x_left, x_right, y, color);
    }
}

void render_plane(mlx_image_t* img, uint32_t plane_color, float aspect_ratio, float fov) {
    float plane_size = 200.0;
    int plane_center_x = img->width / 2; // Center of the image
    int plane_center_y = img->height / 2; // Center of the image
    float camera_distance = 400.0; // Distance from camera to the projection plane

    // Define the corners of the plane
    float corners[4][3] = {
        {-plane_size, 0, -plane_size}, // Bottom-left
        { plane_size, 0, -plane_size}, // Bottom-right
        { plane_size, 0,  plane_size}, // Top-right
        {-plane_size, 0,  plane_size}  // Top-left
    };

    // Define the indices for the two triangles that make up the plane
    unsigned int indices[6] = {0, 1, 2, 2, 3, 0};

    // Convert FOV from degrees to radians
    float fov_radians = fov * (PI / 180.0);

    // Calculate the perspective projection scaling factors
    float scale_x = tan(fov_radians / 2.0) * aspect_ratio;
    float scale_y = tan(fov_radians / 2.0);

    // Render the plane using its corners
    for (int i = 0; i < 6; i += 3) {
        // Get the vertices of the current triangle
        float x1 = corners[indices[i]][0];
        float y1 = corners[indices[i]][1];
        float z1 = corners[indices[i]][2];

        float x2 = corners[indices[i+1]][0];
        float y2 = corners[indices[i+1]][1];
        float z2 = corners[indices[i+1]][2];

        float x3 = corners[indices[i+2]][0];
        float y3 = corners[indices[i+2]][1];
        float z3 = corners[indices[i+2]][2];

        // Apply perspective projection
        float projected_x1 = (x1 * scale_x * camera_distance) / (camera_distance + z1) + plane_center_x;
        float projected_y1 = (y1 * scale_y * camera_distance) / (camera_distance + z1) + plane_center_y;

        float projected_x2 = (x2 * scale_x * camera_distance) / (camera_distance + z2) + plane_center_x;
        float projected_y2 = (y2 * scale_y * camera_distance) / (camera_distance + z2) + plane_center_y;

        float projected_x3 = (x3 * scale_x * camera_distance) / (camera_distance + z3) + plane_center_x;
        float projected_y3 = (y3 * scale_y * camera_distance) / (camera_distance + z3) + plane_center_y;

        // Draw the triangle by plotting its projected points
        draw_triangle(img, (int)projected_x1, (int)projected_y1, (int)projected_x2, (int)projected_y2, (int)projected_x3, (int)projected_y3, plane_color);
    }
}
