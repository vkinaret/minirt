#include "minirt.h"

static char    *ft_strncat(char *s1, const char *s2, size_t n)
 {
     size_t  i;
     size_t  len;
  
     i = 0;
     len = ft_strlen(s1);
     while (i < n && s2[i])
     {
         s1[len + i] = s2[i];
         i++;
     }
     s1[len + i] = 0;
     return (s1);
 }

void		fatal(char *message)
{
	char error_message[100];

	ft_strlcpy(error_message, "[!!] Fatal Error ",100);
	ft_strncat(error_message, message, 83);
	perror(error_message);
	exit(EXIT_FAILURE);
}

void		scene_error(char *message)
{
	char error_message[100];

	ft_strlcpy(error_message, "Scene Error: ",100);
	ft_strncat(error_message, message, 87);
	ft_putstr_fd(error_message, 2);
	exit(EXIT_FAILURE);
}

void		*secure_malloc(unsigned int size)
{
	void *ptr;

	ptr = malloc(size);
	if (ptr == NULL)
		fatal("in malloc() on memory allocation");
	return (ptr);
}

void		usage(char *program_name)
{
	printf("Usage: %s <scene.rt>\n", program_name);
	exit(EXIT_FAILURE);
}

#ifndef LINUX

int			mlx_get_screen_size(void *mlx_ptr, int *sizex, int *sizey)
{
	mlx_ptr = (int*)mlx_ptr;
	sizex = sizey;
	return (0);
}
#endif
