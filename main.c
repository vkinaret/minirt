/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinaret <vkinaret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:53:11 by vkinaret          #+#    #+#             */
/*   Updated: 2024/08/23 23:49:03 by vkinaret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	exit_window(mlx_key_data_t keydata, void *ptr)
{
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		mlx_close_window(ptr);
		return ;
	}
}

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
	int	p = 1;
	int s = 1;
	int c = 1;
	t_object *object = scene->objects;
	
	printf("\nPrinting struct...\n\n");
	printf("Ambient has ratio of %f\n", scene->ambient->ratio);
	printf("Ambient has color of %d, %d, %d\n", scene->ambient->color.r, scene->ambient->color.g, scene->ambient->color.b);
	printf("Ambient has hex value of #%x\n\n", scene->ambient->color.hex);
	printf("Light has coordinates of %f, %f, %f (xyz)\n", scene->light->point.x, scene->light->point.y, scene->light->point.z);
	printf("Light has ratio of %f\n", scene->light->ratio);
	printf("Light has color of %d, %d, %d\n", scene->light->color.r, scene->light->color.g, scene->light->color.b);
	printf("Light has hex value of #%x\n\n", scene->light->color.hex);
	printf("Camera has pov of %f, %f, %f (xyz)\n", scene->camera->pov.x, scene->camera->pov.y, scene->camera->pov.z);
	printf("Camera has vector of %f, %f, %f (xyz)\n", scene->camera->vector.x, scene->camera->vector.y, scene->camera->vector.z);
	printf("Camera has fov of %d\n\n", scene->camera->fov);
	while (object != NULL)
	{
		if (object->id == 'P')
		{
			printf("Plane %d has coordinates of %f, %f, %f (xyz)\n", p, object->point.x, object->point.y, object->point.z);
			printf("Plane %d has vector of %f, %f, %f (xyz)\n", p, object->vector.x, object->vector.y, object->vector.z);
			printf("Plane %d has color of %d, %d, %d\n\n", p, object->color.r, object->color.g, object->color.b);
			p++;
		}
		else if (object->id == 'S')
		{
			printf("Sphere %d has coordinates of %f, %f, %f\n", s, object->point.x, object->point.y, object->point.z);
			printf("Sphere %d has diameter of %f\n", s, object->diameter);
			printf("Sphere %d has color of %d, %d, %d\n\n", s, object->color.r, object->color.g, object->color.b);
			s++;
		}
		else if (object->id == 'C')
		{
			printf("Cylinder %d has coordinates of %f, %f, %f\n", c, object->point.x, object->point.y, object->point.z);
			printf("Cylinder %d has vector of %f, %f, %f (xyz)\n", c, object->vector.x, object->vector.y, object->vector.z);
			printf("Cylinder %d has diameter of %f\n", c, object->diameter);
			printf("Cylinder %d has height of %f\n", c, object->height);
			printf("Cylinder %d has color of %d, %d, %d\n\n", c, object->color.r, object->color.g, object->color.b);
			c++;
		}
		object = object->next;
	}
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
		
	//parsing here
	list = parse_file(argv[1], NULL, NULL);
	if (!list)
		return (1);
	print_list(list); //to check the contents of the list
	
	//init here
	scene = init_struct(list, NULL);
	if (!scene)
	{
		ft_lstclear(&list, free);
		return (1);
	}
	print_scene(scene); //to check the contents of the struct
	ft_lstclear(&list, free);
	
	//rendering here
	mlx_t	*mlx;
	mlx_image_t* img;
	//uint32_t sphere_color = 0x00FFFF;
	//uint32_t cylinder_color = 0xC5337B;
    uint32_t box_color = 0xE2E2E2;
	
	mlx = mlx_init(900, 600, "minirt", true);
	if (mlx == NULL)
		return (printf("mlx init failed"));

	img = mlx_new_image(mlx, 900, 600);
	if (!img) 
	{
		mlx_terminate(mlx);
		return (1);
	}

	int light_x = -2500;
    int light_y = -50;
    int light_z = -100;
    float ambient_intensity = 0.7f;
    float ambient_reflectivity = 0.8f;
    float camera_x = 0.0;
    float camera_y = -200;
    float camera_z = -300;
	float aspect_ratio = 1600.0 / 1200.0;
    float fov = 90.0;
	
	render_plane(img, box_color, light_x, light_y, light_z, aspect_ratio, fov, ambient_intensity, ambient_reflectivity, camera_x, camera_y, camera_z);
    //render_sphere(img, sphere_color, light_x, light_y, light_z, aspect_ratio, fov, ambient_intensity, ambient_reflectivity, camera_x, camera_y, camera_z);
    //render_cylinder(img, cylinder_color, light_x, light_y, light_z, aspect_ratio, fov, ambient_intensity, ambient_reflectivity, camera_x, camera_y, camera_z);

	mlx_image_to_window(mlx, img, 0, 0);
	mlx_key_hook(mlx, (mlx_keyfunc)exit_window, mlx);
	mlx_loop(mlx);
	mlx_delete_image(mlx, img);
	mlx_terminate(mlx);
	
	//before freeing the scene, free each malloc inside the struct
	free(scene);
	return (0);
}
