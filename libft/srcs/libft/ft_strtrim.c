/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stuna <stuna@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:18:08 by stuna             #+#    #+#             */
/*   Updated: 2023/11/08 13:12:19 by stuna            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*str;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1) - 1;
	while (ft_strchr(set, s1[start]) && start <= end)
		start++;
	if (start > end)
		return (ft_strdup(s1 + end + 1));
	while (ft_strchr(set, s1[end]) && end >= 0)
		end--;
	str = malloc(end - start + 2);
	if (!str)
		return (NULL);
	ft_strlcpy(str, &s1[start], end - start + 2);
	return (str);
}
/*
#include <stdio.h>

int main() {
    char const *s1 = "  Hello, world!  ";
    char const *set = " H!o0";
    char *trimmed_string;

    trimmed_string = ft_strtrim(s1, set);

    printf("Original string: \"%s\"\n", s1);
    printf("Set of characters to trim: \"%s\"\n", set);
    printf("Trimmed string: \"%s\"\n", trimmed_string);

    // Free allocated memory
    free(trimmed_string);

    return 0;
}*/
