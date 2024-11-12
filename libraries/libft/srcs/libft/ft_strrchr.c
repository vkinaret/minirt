/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stuna <stuna@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:13:43 by stuna             #+#    #+#             */
/*   Updated: 2023/11/09 18:32:09 by stuna            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(char const *str, int c)
{
	char const	*pstr;
	int			i;

	pstr = NULL;
	i = 0;
	while (str[i])
	{
		if (str[i] == (char)c)
		{
			pstr = &str[i];
		}
		i++;
	}
	if (str[i] == (char)c)
	{
		return ((char *)&str[i]);
	}
	else
	{
		return ((char *)pstr);
	}
}
