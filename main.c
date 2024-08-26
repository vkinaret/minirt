/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinaret <vkinaret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:53:11 by vkinaret          #+#    #+#             */
/*   Updated: 2024/08/26 15:07:09 by vkinaret         ###   ########.fr       */
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
			printf("Plane %d has color of %d, %d, %d\n", p, object->color.r, object->color.g, object->color.b);
			printf("Plane %d has hex value of #%x\n\n", p, object->color.hex);
			p++;
		}
		else if (object->id == 'S')
		{
			printf("Sphere %d has coordinates of %f, %f, %f\n", s, object->point.x, object->point.y, object->point.z);
			printf("Sphere %d has diameter of %f\n", s, object->diameter);
			printf("Sphere %d has color of %d, %d, %d\n", s, object->color.r, object->color.g, object->color.b);
			printf("Sphere %d has hex value of #%x\n\n", s, object->color.hex);
			s++;
		}
		else if (object->id == 'C')
		{
			printf("Cylinder %d has coordinates of %f, %f, %f\n", c, object->point.x, object->point.y, object->point.z);
			printf("Cylinder %d has vector of %f, %f, %f (xyz)\n", c, object->vector.x, object->vector.y, object->vector.z);
			printf("Cylinder %d has diameter of %f\n", c, object->diameter);
			printf("Cylinder %d has height of %f\n", c, object->height);
			printf("Cylinder %d has color of %d, %d, %d\n", c, object->color.r, object->color.g, object->color.b);
			printf("Cylinder %d has hex value of #%x\n\n", c, object->color.hex);
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
	scene = init_scene(list, NULL);
	if (!scene)
	{
		ft_lstclear(&list, free);
		return (1);
	}
	print_scene(scene); //to check the contents of the struct
	ft_lstclear(&list, free);
	
	//rendering here
	render_objects(scene);
	
	mlx_image_to_window(scene->mlx, scene->img, 0, 0);
	mlx_key_hook(scene->mlx, (mlx_keyfunc)exit_window, scene->mlx);
	mlx_loop(scene->mlx);
	mlx_delete_image(scene->mlx, scene->img);
	mlx_terminate(scene->mlx);
	
	//before freeing the scene, free each malloc inside the struct
	free(scene);
	return (0);
}
