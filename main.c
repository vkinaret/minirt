/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinaret <vkinaret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:53:11 by vkinaret          #+#    #+#             */
/*   Updated: 2024/07/17 15:07:45 by vkinaret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
		return (printf("Error\nThis program takes one argument!\n"));
	if (check_extension(argv[1], 0))
		return (printf("Error\nThe argument must be in .rt format.\n"));
	
	//PARSING
	/*if (parse_file(argv[1], NULL, NULL))
		return (1);*/
	
	//WINDOW MANAGEMENT
	/*mlx_t	*mlx;
	int32_t	width = 50;
	int32_t	height = 50;
	mlx = mlx_init(32 * width, 32 * height, "minirt", true);
	if (mlx == NULL)
		return (printf("mlx init failed"));
	mlx_key_hook(mlx, (mlx_keyfunc)exit_window, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);*/
    return (0);
}
