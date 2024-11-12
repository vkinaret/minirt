/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinaret <vkinaret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:32:40 by stuna             #+#    #+#             */
/*   Updated: 2024/11/12 16:55:32 by vkinaret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	parse(t_mlx *mlx, t_scene *data, t_figures **lst, char *obj)
{
	if (!ft_strncmp(obj, "A ", 2))
		parse_ambient(data, obj + 1);
	else if (!ft_strncmp(obj, "C ", 2))
		parse_camera(mlx, obj + 1);
	else if (!ft_strncmp(obj, "L ", 2))
		parse_light(&data, obj + 1);
	else if (!ft_strncmp(obj, "pl ", 3))
		parse_plane(lst, obj + 2);
	else if (!ft_strncmp(obj, "sp ", 3))
		parse_sphere(lst, obj + 2);
	else if (!ft_strncmp(obj, "cy ", 3))
		parse_cylinder(lst, obj + 2);
	else
		scene_error("Error parsing the config file.\n");
}

static int	dupcheck(char *str, char id)
{
	int		i;
	int		c;

	i = 0;
	c = 0;
	while (str[i])
	{
		if (str[i] == id)
			c++;
		i++;
	}
	if (c > 1)
		return (1);
	return (0);
}

static void	parse_elems(t_mlx *mlx, t_scene *data, t_figures **lst, char *str)
{
	int		i;
	char	**obj;

	i = 0;
	obj = NULL;
	data->xres = 1000;
	data->yres = 1000;
	if (dupcheck(str, 'A') || dupcheck(str, 'C') || dupcheck(str, 'L'))
		scene_error("A, L and C can only be declared once per scene.\n");
	obj = ft_split(str, '\n');
	if (obj == NULL)
		scene_error("Malloc error.\n");
	while (obj[i])
	{
		parse(mlx, data, lst, obj[i]);
		i++;
	}
	free(obj);
	if (mlx->cam == NULL)
		scene_error("Not enough elements to render a scene.\n");
}

void	parse_scene(t_mlx *mlx, t_scene *data, t_figures **lst, char **av)
{
	char		*str;
	int			fd;

	*lst = NULL;
	data->l = NULL;
	mlx->cam = NULL;
	printf("Preparing the %s file scene...\n", av[1]);
	str = (char *)secure_malloc(sizeof(char) * (BUFSIZE + 1));
	fd = open(av[1], 0);
	if (fd == -1)
		fatal("when opening the .rt file");
	str = readfile(str, fd);
	if (str == NULL || *str == '\0')
		scene_error("The file was empty!");
	parse_elems(mlx, data, lst, str);
	free(str);
}
