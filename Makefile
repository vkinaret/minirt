NAME	= miniRT

HEAD	= headers

SRCDIR	= sources/

LIB	= libraries/

FILES	=	main.c \
			parser.c \
			parse_things.c \
			parse_objects.c \
			multithreading.c \
			camera.c \
			intersect_sphere.c \
			intersect_plane.c \
			intersect_cylinder.c \
			intersect_utils.c \
			lightning.c \
			distribute_pixels.c \
			anti_alias.c \
			color_computation.c \
			error_handling.c \
			parsing_utils1.c \
			parsing_utils2.c \
			parsing_utils3.c \
			utils1.c \
			utils2.c \
			utils3.c \

SRCS	= $(addprefix $(SRCDIR), $(FILES))

OBJS	= ${SRCS:.c=.o}

CC		= cc -g

RM		= rm -f

CFLAGS	= -Wall -Wextra -Werror -I $(HEAD) -D NUM_THREADS=$(NUM_THREADS)

FLAGS = -L $(LIB)libft -lft -L $(LIB)vectors -lvct

MACOS_MACRO = -D MACOS

LINUX_MACRO = -D LINUX

MACOS_FLAGS	= -L $(LIB)minilibx_opengl_20191021 -lmlx -framework OpenGL -framework AppKit 

LINUX_FLAGS = -L $(LIB)minilibx-linux -lmlx -lm -lX11 -lXext -lpthread

UNAME := $(shell uname)

ifeq ($(UNAME),Darwin)
	NUM_THREADS = $(shell sysctl -n hw.ncpu)
	CFLAGS += $(MACOS_MACRO)
	FLAGS += $(MACOS_FLAGS)
endif
ifeq ($(UNAME),Linux)
	NUM_THREADS = $(shell nproc --all)
	CFLAGS += $(LINUX_MACRO)
	FLAGS += $(LINUX_FLAGS)
endif

${NAME}:	${OBJS}
			make -C $(LIB)libft
			make -C $(LIB)vectors
			${CC} ${CFLAGS} $(OBJS) $(FLAGS) -o ${NAME}

all:		${NAME}

clean:
			make clean -C $(LIB)libft
			make clean -C $(LIB)vectors
			${RM} ${OBJS}

fclean:		clean
			make fclean -C $(LIB)libft
			make fclean -C $(LIB)vectors
			${RM} ${NAME}

re:			fclean all

PHONY:		all clean fclean re
