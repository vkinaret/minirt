/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinaret <vkinaret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:01:12 by vkinaret          #+#    #+#             */
/*   Updated: 2024/06/24 15:26:31 by vkinaret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	size_t		i;

	if (dst == NULL && src == NULL)
		return (NULL);
	if (dst < src)
	{
		i = 0;
		while (i < n)
		{
			((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	if (dst > src && n != 0)
	{
		i = n;
		while (--i > 0)
		{
			((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
			if (i == 0)
				break ;
		}
	}
	return (dst);
}
