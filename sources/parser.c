#include "minirt.h"


static void		parse(t_minilibx *mlx, t_scene *data, t_figures **lst,
																char **strptr)
{
	char *str;

	str = *strptr;
	if (*str == 'R' && *(str++))
		parse_res(data, &str);
	else if (*str == 'A' && *(str++))
		parse_ambient_light(data, &str);
	else if (*str == 'c' && (*(str + 1) == 32 || *(str + 1) == 9) && *(str++))
		parse_camera(mlx, data, &str);
	else if (*str == 'c' && *(str + 1) == 'y' && *(str++) && *(str++))
		parse_cylinder(lst, &str);
	else if (*str == 'l' && (*(str + 1) == 32 || *(str + 1) == 9) && *(str++))
		parse_light(&data, &str);
	else if (*str == 's' && *(str + 1) == 'p' && *(str++) && *(str++))
		parse_sphere(lst, &str);
	else if (*str == 'p' && *(str + 1) == 'l' && *(str++) && *(str++))
		parse_plane(lst, &str);
	*strptr = str;
}

static void		parse_elems(t_minilibx *mlx, t_scene *data, t_figures **lst,
																	char *str)
{
	data->res_init = 0;
	data->al_init = 0;
	while (*str)
	{
		if (*str == '#')
		{
			while (*str && *str != '\n')
				str++;
		}
		else
			parse(mlx, data, lst, &str);
		str++;
	}
	if (data->res_init == 0 || data->al_init == 0 || mlx->cam == NULL)
		scene_error("Not enough elements to render a scene\n");
}

void			parse_scene(t_minilibx *mlx, t_scene *data, t_figures **lst,
																	char **av)
{
	char		*str;
	int			fd;

	*lst = NULL;
	data->l = NULL;
	mlx->cam = NULL;
	printf("Preparing the %s file scene...\n", av[1]);
	str = (char *)secure_malloc(sizeof(char) * (BUFSIZE + 1));
	if ((fd = open(av[1], 0)) == -1)
		fatal("when opening the .rt file");
	str = readfile(str, fd);
	parse_elems(mlx, data, lst, str);
	free(str);
}
