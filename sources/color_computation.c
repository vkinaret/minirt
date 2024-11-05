#include "minirt.h"

int adjust_color_brightness(int color, double coefficient) {
    const int mask = 255;
    int red = coefficient * ((color & (mask << 16)) >> 16);
    int green = coefficient * ((color & (mask << 8)) >> 8);
    int blue = coefficient * (color & mask);

    red = (red > 255) ? 255 : red;
    green = (green > 255) ? 255 : green;
    blue = (blue > 255) ? 255 : blue;

    return ((red << 16) | (green << 8) | blue);
}
int add_colors(int color1, int color2) {
    const int mask = 255;
    int red = ((color1 & (mask << 16)) + (color2 & (mask << 16))) & (mask << 16);
    int green = ((color1 & (mask << 8)) + (color2 & (mask << 8))) & (mask << 8);
    int blue = ((color1 & mask) + (color2 & mask)) & mask;

    return (red | green | blue);
}

int modulate_color_with_light(int color, t_p3 light_rgb) {
    unsigned int mask = 255 << 16;
    unsigned int red = light_rgb.x * ((color & mask) >> 16);
    mask >>= 8;
    unsigned int green = light_rgb.y * ((color & mask) >> 8);
    mask >>= 8;
    unsigned int blue = light_rgb.z * (color & mask);

    red = (red > 255) ? 255 : red;
    green = (green > 255) ? 255 : green;
    blue = (blue > 255) ? 255 : blue;

    return ((red << 16) | (green << 8) | blue);
}



int calculate_color_difference(int color1, int color2) {
    const int mask = 255;
    int red_diff[2], green_diff[2], blue_diff[2];

    red_diff[0] = (color1 & (mask << 16)) >> 16;
    green_diff[0] = (color1 & (mask << 8)) >> 8;
    blue_diff[0] = color1 & mask;

    red_diff[1] = (color2 & (mask << 16)) >> 16;
    green_diff[1] = (color2 & (mask << 8)) >> 8;
    blue_diff[1] = color2 & mask;

    int color_distance_squared = pow((red_diff[1] - red_diff[0]), 2)
                               + pow((green_diff[1] - green_diff[0]), 2)
                               + pow((blue_diff[1] - blue_diff[0]), 2);

    return (color_distance_squared > 1000);
}


