/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinaret <vkinaret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:31:38 by vkinaret          #+#    #+#             */
/*   Updated: 2024/07/22 20:43:27 by vkinaret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int ft_free(char *line)
{
    free(line);
    return (1);
}

static void print_list(t_list *list)
{
    t_list *temp;

    temp = list;
	printf("Printing list...\n");
    while (temp)
    {
        printf("%s", (char *)temp->content);
        temp = temp->next;
    }
}

static int check_identifier(char *line)
{
    if (!ft_strncmp(line, "A ", 2))
        return (parse_ambient(line + 1));
    if (!ft_strncmp(line, "C ", 2))
		return (parse_camera(line + 1));
	if (!ft_strncmp(line, "L ", 2))
		return (parse_light(line + 1));
	if (!ft_strncmp(line, "pl ", 2))
        return (parse_plane(line + 2));
    if (!ft_strncmp(line, "sp ", 2))
        return (parse_sphere(line + 2));
    if (!ft_strncmp(line, "cy ", 2))
		return (parse_cylinder(line + 2));
    return (print_error(WRONG_ID));
}

static int dupcheck(t_list *list, char *id)
{
    int     c;
    t_list  *temp;

    c = 0;
    temp = list;
    while (temp)
    {
        if (!ft_strncmp(temp->content, id, 2))
            c++;
        temp = temp->next;
    }
    if (c > 1)
        return (1);
    return (0);
}

static int parse_list(t_list *list)
{
    t_list *temp;

    temp = list;
    if (temp == NULL)
        return (print_error(EMPTY_FILE));
    if (dupcheck(list, "A ") || dupcheck(list, "C ") || dupcheck(list, "L "))
        return (print_error(DUPLICATE));
    while (temp)
    {
        if (check_identifier(temp->content))
            return (1);
        temp = temp->next;
    }
    return (0);
}

t_list *parse_file(char *argv, t_list *list, t_list *new_node)
{
    int fd;
    char *line;
    
    fd = open(argv, O_RDONLY);
	while (true)
    {
        line = get_next_line(fd, 0, 0, NULL);
		if (line == NULL && ft_free(line))
            break ;
		else if (line[0] == '\n' && ft_free(line))
            continue ;
        new_node = ft_lstnew(line);
        ft_lstadd_back(&list, new_node);
    }
    if (parse_list(list))
    {
        ft_lstclear(&list, free);
	    close(fd);
        return (NULL);
    }
	print_list(list);
    ft_lstclear(&list, free);
    close(fd);
    return (list);
}
