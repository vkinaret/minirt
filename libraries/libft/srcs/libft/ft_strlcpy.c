/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stuna <stuna@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:29:28 by stuna             #+#    #+#             */
/*   Updated: 2023/11/09 17:24:08 by stuna            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *to, const char *from, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize > 0)
	{
		while (from[i] != '\0' && i < dstsize - 1)
		{
			to[i] = from[i];
			i++;
		}
		to[i] = '\0';
	}
	while (from[i] != '\0')
	{
		i++;
	}
	return (i);
}
