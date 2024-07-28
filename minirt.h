/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinaret <vkinaret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 13:39:52 by vkinaret          #+#    #+#             */
/*   Updated: 2024/07/28 17:09:36 by vkinaret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "MLX42/include/MLX42/MLX42.h"
# include "LIBFT/libft.h"
# include <stdio.h> //for printf and perror
#include <fcntl.h> //for open
#include <unistd.h> //for read, write and close
#include <stdlib.h> //for malloc, free and exit
#include <string.h> //for strerror
#include <errno.h> //for errno
#include <math.h> //for math functions
#include <stdint.h> //for uint32

#define PI 3.14159265

enum    e_error
{
    SUCCESS = 0,
    ARGUMENT_COUNT,
    FILE_FORMAT,
    WRONG_ID,
    EMPTY_FILE,
    DUPLICATE,
    NEWLINE,
    RATIO,
    COLOR,
    COORDINATES,
    VECTOR,
    FOV,
    DIAMETER,
    HEIGHT
};

typedef struct  s_rgb
{
    int r;
    int g;
    int b;
}               t_rgb;

typedef struct  s_object
{
    int     type; //sphere, plane, cylinder
    int     coords[3]; //width (x), height (y), length (z)
    int     vector[3]; //plane and cylinder only
    int     diameter; //sphere and cylinder only
    int     height; //cylinder only
    t_rgb   color;
}               t_object;

typedef struct  s_light
{
    int coords[3]; //width (x), height (y), length (z)
    int ratio; //ambient and diffuse only
    t_rgb   color;
}               t_light;

typedef struct  s_camera
{
    double  pov[3];
    double  vector[3];
    int     fov;
}               t_camera;

typedef struct  s_scene
{
    t_light     ambient;
    t_light     light;
    t_camera    camera;
    t_object    *objects;
}               t_scene;

//PARSE
t_list  *parse_file(char *argv, t_list *list, t_list *new_node);
int     parse_ambient(char *line);
int     parse_camera(char *line);
int     parse_light(char *line);
int     parse_plane(char *line);
int     parse_sphere(char *line);
int     parse_cylinder(char *line);

//PARSE UTINGS
int     parse_coordinates(char *line, int i, int count);
int     parse_color(char *line, int i, int count);
int     parse_ratio(char *line, int i);
int     parse_vector(char *line, int i, int count);

//ERROR
int print_error(int err, int code);

//RENDER
uint32_t    calculate_lighting(float x, float y, float z, uint32_t sphere_color, int light_x, int light_y, int light_z);
void        render_sphere(mlx_image_t* img, uint32_t sphere_color, int light_x, int light_y, int light_z, float aspect_ratio, float fov);


#endif