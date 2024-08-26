/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinaret <vkinaret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 13:39:52 by vkinaret          #+#    #+#             */
/*   Updated: 2024/08/26 09:41:24 by vkinaret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "MLX42/include/MLX42/MLX42.h"
# include "LIBFT/libft.h"
# include <stdio.h> //for printf and perror
# include <fcntl.h> //for open
# include <unistd.h> //for read, write and close
# include <stdlib.h> //for malloc, free and exit
# include <string.h> //for strerror
# include <errno.h> //for errno
# include <math.h> //for math functions
# include <stdint.h> //for uint32

# define PI 3.14159265358979323846

enum	e_error
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

typedef uint32_t	t_int;

typedef struct s_xyz
{
	double	x;
	double	y;
	double	z;
}				t_xyz;

typedef struct s_rgb
{
	int		r;
	int		g;
	int		b;
	t_int	hex;
}				t_rgb;

typedef struct s_object
{
	int				id;
	t_xyz			point;
	t_xyz			vector;
	double			diameter;
	double			height;
	t_rgb			color;
	struct s_object	*next;
}				t_object;

typedef struct s_light
{
	t_xyz	point;
	double	ratio;
	t_rgb	color;
}				t_light;

typedef struct s_camera
{
	t_xyz	pov;
	t_xyz	vector;
	int		fov;
}				t_camera;

typedef struct s_scene
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_light		*ambient;
	t_light		*light;
	t_camera	*camera;
	t_object	*objects;
}				t_scene;

t_list		*parse_file(char *argv, t_list *list, t_list *new_node);
int			parse_ambient(char *line);
int			parse_camera(char *line);
int			parse_light(char *line);
int			parse_plane(char *line);
int			parse_sphere(char *line);
int			parse_cylinder(char *line);
int			parse_coordinates(char *line, int i, int count);
int			parse_color(char *line, int i, int count);
int			parse_ratio(char *line, int i);
int			parse_vector(char *line, int i, int count);
t_scene		*init_scene(t_list *list, t_scene *scene);
t_rgb		init_color(char *line);
t_xyz		init_point(char *line);
double  	init_ratio(char *line, int flag);
t_xyz		init_vector(char *line);
double		init_diameter(char *line);
double		init_height(char *line);
t_light 	*init_light_two(t_light *light, char *content);
t_camera 	*init_camera_two(t_camera *camera, char *content);
t_object	*init_objects(t_list *list, char *content);
t_object    *init_cylinder_two(t_object *cylinder, char *content);
int			print_error(int err, int code);
void		render_objects(t_scene *scene);

uint32_t calculate_lighting(float x, float y, float z, uint32_t sphere_color, int light_x, int light_y, int light_z, float ambient_intensity, float ambient_reflectivity);
void render_sphere(mlx_image_t* img, uint32_t sphere_color, int light_x, int light_y, int light_z, float aspect_ratio, float fov,float ambient_intensity,float ambient_reflectivity,float camera_x, float camera_y, float camera_z);
void render_cylinder(mlx_image_t* img, uint32_t cylinder_color, int light_x, int light_y, int light_z, float aspect_ratio, float fov,float ambient_intensity,float ambient_reflectivity, float camera_x, float camera_y, float camera_z);
void render_plane(mlx_image_t* img, uint32_t box_color, int light_x, int light_y, int light_z, float aspect_ratio, float fov, float ambient_intensity, float ambient_reflectivity, float camera_x, float camera_y, float camera_z);



#endif