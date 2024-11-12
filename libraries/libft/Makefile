# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: stuna <stuna@student.hive.fi>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/06 16:11:38 by stuna             #+#    #+#              #
#    Updated: 2023/11/15 13:42:20 by stuna            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

HEADER = libft.h

NAME = libft.a

CC = cc

CFLAGS = -Wall -Wextra -Werror -I includes

LIBFT_F	= ft_isprint.c \
	ft_putendl_fd.c \
	ft_strlcat.c \
	ft_substr.c \
	ft_atoi.c \
	ft_itoa.c \
	ft_putnbr_fd.c \
	ft_strlcpy.c \
	ft_tolower.c \
	ft_bzero.c \
	ft_memchr.c \
	ft_putstr_fd.c \
	ft_strlen.c \
	ft_toupper.c \
	ft_calloc.c \
	ft_memcmp.c \
	ft_split.c \
	ft_strmapi.c \
	ft_isalnum.c \
	ft_memcpy.c \
	ft_strchr.c \
	ft_strncmp.c \
	ft_isalpha.c \
	ft_memmove.c \
	ft_strdup.c \
	ft_strnstr.c \
	ft_isascii.c \
	ft_memset.c \
	ft_striteri.c \
	ft_strrchr.c \
	ft_isdigit.c \
	ft_putchar_fd.c \
	ft_strjoin.c \
	ft_strtrim.c \



BSRCS := ft_lstadd_back_bonus.c \
	ft_lstadd_front_bonus.c \
	ft_lstclear_bonus.c \
	ft_lstdelone_bonus.c \
	ft_lstiter_bonus.c \
	ft_lstlast_bonus.c \
	ft_lstmap_bonus.c \
	ft_lstnew_bonus.c \
	ft_lstsize_bonus.c \

SRCS	=  $(addprefix srcs/libft/, $(LIBFT_F))

OBJS := $(SRCS:.c=.o)

BOBJS := $(BSRCS:.c=.o)

RM		= rm -f

.c.o:
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			ar rc ${NAME} ${OBJS}
			ranlib ${NAME}

all:		${NAME}

clean:
			${RM} ${OBJS}


fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re
