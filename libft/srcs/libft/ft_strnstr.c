/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stuna <stuna@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:09:26 by stuna             #+#    #+#             */
/*   Updated: 2023/11/06 17:09:28 by stuna            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *bigstr, const char *shrt, size_t len)
{
	size_t	i;
	size_t	j;

	if (shrt[0] == '\0')
		return ((char *)bigstr);
	i = 0;
	while (bigstr[i] != '\0' && len > 0)
	{
		j = 0;
		while (bigstr[i + j] == shrt[j] && shrt[j] != '\0' && j < len)
		{
			if (shrt[j + 1] == '\0')
				return ((char *)&bigstr[i]);
			j++;
		}
		i++;
		len--;
	}
	return (NULL);
}
