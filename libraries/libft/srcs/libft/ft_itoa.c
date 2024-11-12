/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stuna <stuna@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:04:43 by stuna             #+#    #+#             */
/*   Updated: 2023/11/09 20:12:42 by stuna            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	spaces(int n)
{
	size_t	i;

	if (n == 0)
		return (1);
	if (n < 0)
		i = 1;
	else
		i = 0;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	long int	nr;
	int			spc;
	char		*nbrstr;
	int			rmd;

	nr = n;
	spc = spaces(n);
	nbrstr = malloc(spc + 1);
	if (nbrstr == NULL)
		return (NULL);
	nbrstr[spc] = '\0';
	if (nr == 0)
		nbrstr[0] = '0';
	if (nr < 0)
	{
		nbrstr[0] = '-';
		nr = -nr;
	}
	while (nr != 0)
	{
		rmd = nr % 10;
		nbrstr[--spc] = rmd + '0';
		nr = nr / 10;
	}
	return (nbrstr);
}
/*
int	main() {
    int num = -235235;
    char *str = ft_itoa(num);
    if (str != NULL) {
        printf("Integer: %d, String: %s\n", num, str);
        free(str); // Free the allocated memory
    }
    return 0;
}*/
