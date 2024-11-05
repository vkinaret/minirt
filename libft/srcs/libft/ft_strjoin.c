/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stuna <stuna@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:17:13 by stuna             #+#    #+#             */
/*   Updated: 2023/11/06 17:17:15 by stuna            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t			len1;
	size_t			len2;
	char			*s3;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	s3 = malloc (len1 + len2 +1);
	if (s3 == NULL)
		return (NULL);
	if (s1 != NULL)
	{
		ft_strlcpy(s3, s1, (len1 + 1));
		if (s2 != NULL)
			ft_strlcat(s3, s2, (len1 + len2 + 1));
	}
	else if (s2 != NULL)
	{
		ft_strlcpy(s3, s2, (len2 + 1));
	}
	return (s3);
}
