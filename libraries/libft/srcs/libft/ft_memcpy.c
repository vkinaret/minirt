/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stuna <stuna@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:19:27 by stuna             #+#    #+#             */
/*   Updated: 2023/11/09 12:18:58 by stuna            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *to, const void *from, size_t numBytes)
{
	const char	*p_from;
	char		*p_to;
	size_t		i;

	if (from == NULL && to == NULL)
	{
		return (NULL);
	}
	p_from = (const char *) from;
	p_to = (char *) to;
	i = 0;
	while (i < numBytes)
	{
		p_to[i] = p_from[i];
		i++;
	}
	return (to);
}
