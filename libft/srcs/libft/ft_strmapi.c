/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stuna <stuna@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:51:05 by stuna             #+#    #+#             */
/*   Updated: 2023/11/06 17:17:36 by stuna            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*str;

	if (s == NULL)
		return (NULL);
	str = malloc((ft_strlen(s) +1));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}
/*
char	thefunc(unsigned int i, char c)
{
	i = 0;
	c = c + 1;

	return (c);
}

#include <stdio.h>

int main ()
{
	char	*s;
	s = "aaaaaabbbbbb";
	printf("before the strmapi: %s\n",s);
	char	*newstr;
	newstr = ft_strmapi(s, thefunc);
	printf("after the strmapi: %s\n",newstr);
	return (0);

}*/
