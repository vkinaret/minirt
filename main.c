/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinaret <vkinaret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:53:11 by vkinaret          #+#    #+#             */
/*   Updated: 2024/08/20 21:19:59 by vkinaret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//INTERFACE
//implement control of translation, rotation and so on via terminal?

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

static void	print_list(t_list *list)
{
	t_list	*temp;

	temp = list;
	printf("Printing list...\n");
	while (temp)
	{
		printf("%s", (char *)temp->content);
		temp = temp->next;
	}
}

static void print_scene(t_scene *scene)
{
	printf("\nPrinting struct...\n");
	printf("A has ratio of %f\n", scene->ambient->ratio);
	printf("A has color of %d, %d, %d\n", scene->ambient->color.r, scene->ambient->color.g, scene->ambient->color.b);
	printf("A has hex value of #%x\n", scene->ambient->color.hex);
	printf("L has coordinates of %f, %f, %f (xyz)\n", scene->light->point.x, scene->light->point.y, scene->light->point.z);
	printf("L has ratio of %f\n", scene->light->ratio);
	printf("L has color of %d, %d, %d\n", scene->light->color.r, scene->light->color.g, scene->light->color.b);
	printf("L has hex value of #%x\n", scene->light->color.hex);
	printf("C has pov of %f, %f, %f (xyz)\n", scene->camera->pov.x, scene->camera->pov.y, scene->camera->pov.z);
	printf("C has vector of %f, %f, %f (xyz)\n", scene->camera->vector.x, scene->camera->vector.y, scene->camera->vector.z);
	printf("C has fov of %d\n", scene->camera->fov);
}

int	main(int argc, char **argv)
{
	t_list *list;
	t_scene	*scene;

	list = NULL;
	if (argc != 2)
		return (print_error(ARGUMENT_COUNT, 1));
	if (check_extension(argv[1], 0))
		return (print_error(FILE_FORMAT, 2));
	list = parse_file(argv[1], NULL, NULL);
	if (!list)
		return (1);
	print_list(list);
	scene = init_struct(list, NULL);
	if (!scene)
	{
		ft_lstclear(&list, free);
		return (1);
	}
	print_scene(scene);
	ft_lstclear(&list, free);
	free(scene);
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
