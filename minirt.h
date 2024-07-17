/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinaret <vkinaret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 13:39:52 by vkinaret          #+#    #+#             */
/*   Updated: 2024/07/17 15:12:44 by vkinaret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "MLX42/include/MLX42/MLX42.h"
# include "LIBFT/libft.h"
# include <stdio.h> //for printf and perror
#include <fcntl.h> //for open
#include <unistd.h> //for read, write and close
#include <stdlib.h> //for malloc, free and exit
#include <string.h> //for strerror
#include <errno.h> //for errno

typedef struct  s_object
{
    int type; //sphere, plane, cylinder, ambient or diffuse
    int origin[3]; //width (x), height (y), length (z)
    int vector[3]; //plane and cylinder only
    int diameter; //sphere and cylinder only
    int height; //cylinder only
    int brightness; //ambient and diffuse only
    int color[3]; //R, G. B
}               t_object;

typedef struct  s_scene
{
    t_object    *objects;
    t_object    ambient;
    t_object    diffuse;
    double      camera_pov[3];
    double      camera_vector[3];
    int         camera_fov;
}               t_scene;

//PARSING
//int	parse_file(char *argv, t_list *list, t_list *new_node);

#endif