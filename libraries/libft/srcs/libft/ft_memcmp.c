/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stuna <stuna@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:15:41 by stuna             #+#    #+#             */
/*   Updated: 2023/11/06 17:15:43 by stuna            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *str1, const void *str2, size_t nr)
{
	const unsigned char	*str1c;
	const unsigned char	*str2c;
	size_t				i;

	i = 0;
	str1c = (const unsigned char *) str1;
	str2c = (const unsigned char *) str2;
	while (i < nr)
	{
		if (str1c[i] != str2c[i])
		{
			return (str1c[i] - str2c[i]);
		}
		i++;
	}
	return (0);
}
