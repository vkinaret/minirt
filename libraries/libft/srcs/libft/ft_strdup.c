/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stuna <stuna@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:07:52 by stuna             #+#    #+#             */
/*   Updated: 2023/11/06 18:46:58 by stuna            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*s2;

	len = ft_strlen(s1);
	if (s1 == NULL)
		return (NULL);
	s2 = malloc((len + 1));
	if (s2 == NULL)
		return (NULL);
	ft_strlcpy(s2, s1, (len +1));
	return (s2);
}
