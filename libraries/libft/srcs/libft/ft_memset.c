/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stuna <stuna@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:26:46 by stuna             #+#    #+#             */
/*   Updated: 2023/11/06 17:26:47 by stuna            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *destp, int chr, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		((char *)destp)[i] = chr;
		i++;
	}
	return (destp);
}
