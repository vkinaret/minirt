#ifndef MINIRT_H
# define MINIRT_H

# include "mlx.h"
# include "ggl_mlx_define.h"
# include "libft.h"
# include "vectors.h"
# include "figures.h"
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include <pthread.h>
# include <stdio.h>

# ifdef MACOS
#  define OS_NAME 1
# endif

# ifdef LINUX
#  define OS_NAME 2
# endif

# define BUFSIZE 50

# ifndef NUM_THREADS
#  define NUM_THREADS 4
# endif


# define SP 0
# define PL 1
# define CY 4


# define EPSILON 0.00001

typedef struct		s_v3
{
	t_p3	o;
	t_p3	d;
}					t_v3;

typedef struct		s_camera
{
	int				init;
	t_p3			o;
	t_p3			nv;
	int				fov;
	void			*img_ptr;
	int				*px_img;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
	struct s_camera	*next;
}					t_camera;

typedef struct		s_light
{
	t_p3			o;
	double			br;
	int				color;
	struct s_light	*next;
}					t_light;

typedef struct		s_scene
{
	int				xres;
	int				yres;
	t_light			*l;
	double			ambient_light;
	int				al_color;
	int				bgr;
}					t_scene;

typedef struct		s_figures
{
	int				flag;
	union u_figures	fig;
	int				color;
	int				specular;
	int				surface;
	t_p3			normal;
	double			wavelength;
	struct s_figures*next;
}					t_figures;

typedef struct		s_minilibx
{
	void			*mlx_ptr;
	void			*win_ptr;
	t_camera		*cam;
	t_camera		*begin;
}					t_minilibx;

typedef t_minilibx	t_mlx;

typedef struct s_intersection
{
    double	id1;
    double	id2;
    t_p3	ip1;
    t_p3	ip2;
}					t_intersection;

typedef struct		s_wrapper
{
	t_minilibx		mlx;
	t_scene			data;
	t_figures		*lst;
	int				tid;
	int				i;
	int				j;
}					t_wrapper;

typedef struct		s_rss
{
	int		limit;
	int		xres;
	int		yres;
	int		i;
	int		j;
}					t_rss;

typedef struct		s_inter
{
	int				color;
	t_p3			normal;
	t_p3			p;

}					t_inter;


typedef struct		s_thread
{
	pthread_t		threads[NUM_THREADS];
	t_wrapper		wrapper[NUM_THREADS];
	int				i;
}					t_thread;

/*
**			 	Parsing functions
*/

void				parse_scene(t_mlx *mlx, t_scene *data, t_figures **lst, char **av);

void				parse_ambient(t_scene *data, char *str);

void				parse_camera(t_minilibx *mlx, char *str);

void				parse_light(t_scene **data, char *str);

void				parse_sphere(t_figures **elem, char *str);

void				parse_plane(t_figures **elem, char *str);

//void				parse_square(t_figures **elem, char *str);

//void				parse_triangle(t_figures **elem, char *str);

void				parse_cylinder(t_figures **elem, char *str);

//void				parse_cube(t_figures **elem, char *str);

//void				parse_pyramid(t_figures **elem, char *str);

/*
**				Parsing help functions
*/

char				*readfile(char *str, int fd);

int					stoi(char **str);

double				stof(char **str);

void				in_range(double nb, double min, double max, char *function);

void				next(char **str);

void				comma(char **str);

t_p3				parse_p3(char **str);

int					parse_color(char **str);

void				ft_addnewlst_back(t_figures **alst);

/*
**				Intersection functions
*/

int					solve_cylinder(double x[2], t_p3 o, t_p3 d, t_figures *lst);

double				solve_surface(t_p3 o, t_p3 d, t_p3 plane_p, t_p3 plane_nv);

t_p3				calc_cy_normal(double x2[2], t_p3 o, t_p3 d, t_figures *lst);

double				sphere_intersection(t_p3 o, t_p3 d, t_figures *lst);

double				plane_intersection(t_p3 o, t_p3 d, t_figures *lst);

double				square_intersection(t_p3 o, t_p3 d, t_figures *lst);

double				triangle_intersection(t_p3 o, t_p3 d, t_figures *lst);

double				cylinder_intersection(t_p3 o, t_p3 d, t_figures *lst);

double				cube_intersection(t_p3 o, t_p3 d, t_figures *lst);

double				pyramid_intersection(t_p3 o, t_p3 d, t_figures *lst);

/*
**				Intersections help functions
*/

void				try_all_intersections(t_v3 ray, t_figures *lst,
											t_figures *clfig, double *clint);

double				solve_plane(t_p3 o, t_p3 d, t_p3 plane_p,
														t_p3 plane_nv);

/*
**				Ray tracing
*/

void				render_scene(t_wrapper *w);

int					trace_ray(t_p3 o, t_p3 d, t_wrapper *w);

int					compute_ray(int n, t_rss rss, t_wrapper *w);

void				calc_normal(t_p3 p, t_p3 d, t_p3 *normal, t_figures *lst);

int					shade(t_p3 o, t_p3 d, t_figures *lst);

void				compute_light(t_inter *inter, t_scene data, t_figures *lst);

/*
**				Super Sampling
*/

int					*sample_pixel(int *edge_color, int last[2], t_rss rss,
																t_wrapper *w);

int					supersample(int *color, t_rss rss, t_wrapper *w);

/*
**				Multithreaded rendering
*/

void				wrapp_data(t_minilibx mlx, t_scene data, t_figures *lst,
															t_wrapper *wrapper);

void				multithreaded_render(t_wrapper wrapper[NUM_THREADS]);

/*
**				Error handling functions and success message
*/

void				*secure_malloc(unsigned int size);

void				fatal(char *message);

void				scene_error(char *message);

void				usage(char *program_name);

void				success_message(int ac);

/*
**				Minilibx functions
*/

void				init_mlx(t_minilibx *mlx, t_scene *data);

void				graphic_loop(t_minilibx mlx, t_scene data);

int 				close_window(int keycode, t_minilibx *mlx);

int					close_program(void *param);

/*
**				Bmp exporter
*/

void				do_the_bmp_thing(t_minilibx mlx, t_scene data, char *name);

/*
**				Color Operations
*/

int					cproduct(int color, double coef);

int					cadd(int color_a, int color_b);

int					color_difference(int color1, int color2);

int					color_x_light(int color, double rgb[3]);

int					average(int color1, int color2);

int					average_supersampled_color(int *color);

int smoothen(int *init_c, t_rss rss, t_wrapper *wrp);


int *compute_pixel_sample(int *edge_colors, int last_colors[2], t_rss sampling_info, t_wrapper *wrapper);


int adjust_color_brightness(int color, double coefficient);
int add_colors(int color1, int color2);
int modulate_color_with_light(int color, t_p3 light_rgb);
int calculate_color_difference(int color1, int color2);

void	assign_dist_x(double *dist, double *x, double dist_value, double x_value);

#endif
