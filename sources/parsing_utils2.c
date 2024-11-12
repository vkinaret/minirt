/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinaret <vkinaret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:47:41 by stuna             #+#    #+#             */
/*   Updated: 2024/11/12 16:06:02 by vkinaret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static char	*ft_strcat(char *dest, char *src)
{
	int	i1;
	int	i2;

	i1 = 0;
	i2 = 0;
	while (dest[i1] != '\0')
		i1++;
	while (src[i2] != '\0')
	{
		dest[i1] = src[i2];
		i1++;
		i2++;
	}
	dest[i1] = '\0';
	return (dest);
}

static char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (*(src + i) != '\0' && i < n)
	{
		*(dest + i) = *(src + i);
		i++;
	}
	while (i < n)
	{
		*(dest + i) = '\0';
		i++;
	}
	return (dest);
}

void	in_range(double nb, double min, double max, char *function)
{
	char	error_message[100];

	if (nb < min || nb > max)
	{
		ft_strncpy(error_message, function, 76);
		ft_strcat(error_message, " parameter out of range\n");
		scene_error(error_message);
	}
}

void	next(char **str)
{
	while (**str == 32)
		(*str)++;
}

void	comma(char **str)
{
	if (**str != ',')
		scene_error("parameters bad formatted\n");
	while (**str == ',')
		(*str)++;
}
