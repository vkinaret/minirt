#include "render.h"

int main() {
    mlx_t* mlx_ptr;
    mlx_image_t* img;
    uint32_t sphere_color = 0xFFFFF;
    uint32_t cylinder_color = 0xC5337B;
    uint32_t box_color = 0xE2E2E2;


    // Initialize mlx
    mlx_ptr = mlx_init(900, 600, "3D Sphere", false);
    if (!mlx_ptr) {
        return 1;
    }

    // Create a new image
    img = mlx_new_image(mlx_ptr, 900, 600);
    if (!img) {
        mlx_terminate(mlx_ptr);
        return 1;
    }

    // Light source position
    int light_x = -2500;
    int light_y = -50;
    int light_z = -100;
    float ambient_intensity = 0.7f; // Example value
    float ambient_reflectivity = 0.8f; // Example value

    // Camera parameters
    float camera_x = 0.0; // Set your desired camera position
    float camera_y = -200;
    float camera_z = -300;

    float aspect_ratio = 1600.0 / 1200.0; // Width / Height
    float fov = 90.0; // Field of view in degrees

    render_plane(img, box_color, light_x, light_y, light_z, aspect_ratio, fov, ambient_intensity, ambient_reflectivity, camera_x, camera_y, camera_z);
    render_sphere(img, sphere_color, light_x, light_y, light_z, aspect_ratio, fov, ambient_intensity, ambient_reflectivity, camera_x, camera_y, camera_z);
    render_cylinder(img, cylinder_color, light_x, light_y, light_z, aspect_ratio, fov, ambient_intensity, ambient_reflectivity, camera_x, camera_y, camera_z);

    // Display the image on the window
    mlx_image_to_window(mlx_ptr, img, 0, 0);

    // Enter the mlx event loop
    mlx_loop(mlx_ptr);

    // Cleanup (although mlx_loop should not return in normal operation)
    mlx_delete_image(mlx_ptr, img);
    mlx_terminate(mlx_ptr);

    return 0;
}
