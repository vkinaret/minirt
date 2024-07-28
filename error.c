/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinaret <vkinaret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 22:00:00 by vkinaret          #+#    #+#             */
/*   Updated: 2024/07/28 16:52:41 by vkinaret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define ERROR1 "This program takes one argument!"
#define ERROR2 "The argument must be in .rt format."
#define ERROR3 "The line must start with a valid identifier."
#define ERROR4 "The file is empty or contains only newline characters."
#define ERROR5 "A, C and L can only be declared once."
#define ERROR6 "Ratio must be between 0.0 and 1.0."
#define ERROR7 "Color must have three values between 0 and 255."
#define ERROR8 "The last attribute must be followed by a newline."
#define ERROR9 "The coordinates must be in x,y,z format."
#define ERROR10 "The vector values have a range between -1 and 1."
#define ERROR11 "The field of view has a range between 0 and 180."
#define ERROR12 "The diameter must be larger than 0."

int print_error(int err, int code)
{
    printf("Error\n");
    if (err == ARGUMENT_COUNT)
        printf("(%d): %s\n", code, ERROR1);
    if (err == FILE_FORMAT)
        printf("(%d): %s\n", code, ERROR2);
    if (err == WRONG_ID)
        printf("(%d): %s\n", code, ERROR3);
    if (err == EMPTY_FILE)
        printf("(%d): %s\n", code, ERROR4);
    if (err == DUPLICATE)
        printf("(%d): %s\n", code, ERROR5);
    if (err == RATIO)
        printf("(%d): %s\n", code, ERROR6);
    if (err == COLOR)
        printf("(%d): %s\n", code, ERROR7);
    if (err == NEWLINE)
        printf("(%d): %s\n", code, ERROR8);
    if (err == COORDINATES)
        printf("(%d): %s\n", code, ERROR9);
    if (err == VECTOR)
        printf("(%d): %s\n", code, ERROR10);
    if (err == FOV)
        printf("(%d): %s\n", code, ERROR11);
    if (err == DIAMETER)
        printf("(%d): %s\n", code, ERROR12);
    return (err);
}
