/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stuna <stuna@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:22:11 by stuna             #+#    #+#             */
/*   Updated: 2023/11/06 17:29:13 by stuna            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *to, const char *from, size_t dstsize)
{
	size_t	i;
	size_t	len_to;
	size_t	len_from;

	i = 0;
	len_to = ft_strlen(to);
	len_from = ft_strlen(from);
	if (dstsize <= len_to)
		return (dstsize + len_from);
	while (from[i] && i < dstsize - len_to - 1)
	{
		to[len_to + i] = from[i];
		i++;
	}
	to[len_to + i] = '\0';
	return (len_to + len_from);
}
/*
int main()
{
    char first[] = "Hellooo ";
    char last[] = ", the world! what is up with you damn boy????";
    int r;
    int size = 16;
    char buffer[size];

    strcpy(buffer,first);
    r = ft_strlcat(buffer,last,size);

    puts(buffer);
    printf("Value returned: %d\n",r);
    if( r > size )
        puts("String truncated");
    else
        puts("String was fully copied");

    return(0);
}*/
