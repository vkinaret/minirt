#include "render.h"

int main() {
    mlx_t* mlx_ptr;
    mlx_image_t* img;
    uint32_t sphere_color = 0xFFFFF;
    uint32_t cylinder_color = 0xFFFFFF;
	uint32_t plane_color = 0xFFFFFF;


    // Initialize mlx
    mlx_ptr = mlx_init(1600, 1200, "3D Sphere", false);
    if (!mlx_ptr) {
        return 1;
    }

    // Create a new image
    img = mlx_new_image(mlx_ptr, 1600, 1200);
    if (!img) {
        mlx_terminate(mlx_ptr);
        return 1;
    }

    // Light source position
    int light_x = 10000;
    int light_y = 0;
    int light_z = -2000;
	float ambient_intensity = 0.5f; // Example value
    float ambient_reflectivity = 0.9f; // Example value

    // Camera parameters
    float aspect_ratio = 1600.0 / 1200.0; // Width / Height
    float fov = 100.0; // Field of view in degrees
	
	render_plane(img, plane_color, aspect_ratio, fov);


    render_sphere(img, sphere_color, light_x, light_y, light_z, aspect_ratio, fov, ambient_intensity, ambient_reflectivity);
	render_cylinder(img, cylinder_color, light_x, light_y, light_z, aspect_ratio, fov, ambient_intensity, ambient_reflectivity);

    // Display the image on the window
    mlx_image_to_window(mlx_ptr, img, 0, 0);

    // Enter the mlx event loop
    mlx_loop(mlx_ptr);

    // Cleanup (although mlx_loop should not return in normal operation)
    mlx_delete_image(mlx_ptr, img);
    mlx_terminate(mlx_ptr);

    return 0;
}
