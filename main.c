/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinaret <vkinaret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:53:11 by vkinaret          #+#    #+#             */
/*   Updated: 2024/07/22 20:42:39 by vkinaret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//INTERFACE
//implement control of translation, rotation and so on via terminal?


//SAFA'S COLOR CALC: should return uint32_t
/*static unsigned int	calculate_color(int iterations)
{
	unsigned int	color;
	double			t;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	if (iterations < MAX_ITERATIONS)
	{
		t = (double)iterations / MAX_ITERATIONS;
		r = (unsigned char)(255 * t);
		g = (unsigned char)(255 * t);
		b = (unsigned char)(128 * (1 - t));
		color = (r << 28) | (g << 16) | b;
	}
	else
		color = 0x000764;
	return (color);
}*/

/*static void	exit_window(mlx_key_data_t keydata, void *ptr)
{
    if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		mlx_close_window(ptr);
		return ;
	}
}*/

static int	check_extension(char *arg, int i)
{
	while (arg[i])
		i++;
	if (i > 3 && arg[i - 1] == 't' && arg[i - 2] == 'r' && arg[i - 3] == '.')
		return (0);
	return (1);
}

int main(int argc, char **argv)
{	
	//ERROR CHECK
	if (argc != 2)
		return (print_error(ARGUMENT_COUNT));
	if (check_extension(argv[1], 0))
		return (print_error(FILE_FORMAT));
	
	//PARSING
	if (!parse_file(argv[1], NULL, NULL))
		return (1);
	
	//WINDOW MANAGEMENT
	/*mlx_t	*mlx;
	mlx_image_t* img;
    uint32_t sphere_color = 0x00FFFF;
	
	mlx = mlx_init(800, 600, "minirt", true);
	if (mlx == NULL)
		return (printf("mlx init failed"));

	img = mlx_new_image(mlx, 800, 600);
    if (!img) 
	{
        mlx_terminate(mlx);
        return (1);
    }

	int light_x = 0;
    int light_y = 0;
    int light_z = -20000;
	float aspect_ratio = 800.0 / 600.0; // Width / Height
    float fov = 60.0; // Field of view in degrees
	render_sphere(img, sphere_color, light_x, light_y, light_z, aspect_ratio, fov);
	mlx_image_to_window(mlx, img, 0, 0);
	mlx_key_hook(mlx, (mlx_keyfunc)exit_window, mlx);
	mlx_loop(mlx);
	mlx_delete_image(mlx, img);
	mlx_terminate(mlx);*/
    return (0);
}
