/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stuna <stuna@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:02:59 by stuna             #+#    #+#             */
/*   Updated: 2023/11/14 11:22:22 by stuna            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

int	ft_atoi(const char *str)
{
	long long		nr;
	int				i;
	int				sgn;

	nr = 0;
	i = 0;
	sgn = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			sgn = -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (nr > LLONG_MAX / 10 || (nr == LLONG_MAX / 10 && str[i] > '7'))
		{
			if (sgn == 1)
				return (-1);
			else
				return (0);
		}
		nr = nr * 10 + (str[i] - '0');
		i++;
	}
	return ((int)(nr * sgn));
}
/*
#include <stdio.h>
int main()
{
	char *c;
	int a;
	int b;

	c = "-9223372036854775809999";
	a = printf("the original : %d\n", atoi(c));
	b = printf("the ft one   : %d\n", ft_atoi(c));
	
	return 0;
}*/
