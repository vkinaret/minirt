/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinaret <vkinaret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 13:39:52 by vkinaret          #+#    #+#             */
/*   Updated: 2024/08/20 20:20:26 by vkinaret         ###   ########.fr       */
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

# define PI 3.14159265

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
	int			type;
	t_xyz		center;
	t_xyz		vector;
	double		diameter;
	double		height;
	t_rgb		color;
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
	t_light		*ambient;
	t_light		*light;
	t_camera	*camera;
	t_object	**objects;
}				t_scene;

t_list	*parse_file(char *argv, t_list *list, t_list *new_node);
int		parse_ambient(char *line);
int		parse_camera(char *line);
int		parse_light(char *line);
int		parse_plane(char *line);
int		parse_sphere(char *line);
int		parse_cylinder(char *line);
int		parse_coordinates(char *line, int i, int count);
int		parse_color(char *line, int i, int count);
int		parse_ratio(char *line, int i);
int		parse_vector(char *line, int i, int count);
t_scene	*init_struct(t_list *list, t_scene *scene);
t_rgb	init_color(char *line);
t_xyz	init_point(char *line);
double  init_ratio(char *line, int i, int len);

int		print_error(int err, int code);

t_int	calculate_lighting(float x, float y, float z, uint32_t sphere_color, int light_x, int light_y, int light_z);
void	render_sphere(mlx_image_t* img, uint32_t sphere_color, int light_x, int light_y, int light_z, float aspect_ratio, float fov);

#endif