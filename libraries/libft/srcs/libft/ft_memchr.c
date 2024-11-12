/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stuna <stuna@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:11:23 by stuna             #+#    #+#             */
/*   Updated: 2023/11/06 17:11:24 by stuna            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t nr)
{
	unsigned char	*stru;
	unsigned char	ch;
	size_t			i;

	i = 0;
	stru = (unsigned char *) str;
	ch = (unsigned char) c;
	while (i < nr)
	{
		if (stru[i] == ch)
		{
			return (&stru[i]);
		}
		i++;
	}
	return (NULL);
}
