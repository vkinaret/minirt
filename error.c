/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinaret <vkinaret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 22:00:00 by vkinaret          #+#    #+#             */
/*   Updated: 2024/07/22 19:28:24 by vkinaret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int print_error(int err_code)
{
    printf("Error\n");
    if (err_code == ARGUMENT_COUNT)
        printf("This program takes one argument!\n");
    if (err_code == FILE_FORMAT)
        printf("The argument must be in .rt format.\n");
    if (err_code == WRONG_ID)
        printf("The line must start with a valid identifier.\n");
    if (err_code == EMPTY_FILE)
        printf("The file is empty or contains only newline characters.\n");
    if (err_code == DUPLICATE)
        printf("A, C and L can only be declared once.\n");
    if (err_code == RATIO)
        printf("Ratio must be between 0.0 and 1.0.\n");
    if (err_code == COLOR)
        printf("Color must have three values between 0 and 255.\n");
    if (err_code == NEWLINE)
        printf("The last attribute must be followed by a newline.\n");
    if (err_code == COORDINATES)
        printf("The coordinates must be in x,y,z format.\n");
    if (err_code == VECTOR)
        printf("The vector values have a range between -1 and 1.\n");
    if (err_code == FOV)
        printf("The field of view has a range between 0 and 180.\n");
    return (err_code);
}
