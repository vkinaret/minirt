NAME = minirt
MLX42 = ./MLX42/build/libmlx42.a
LIBFT = ./LIBFT/libft.a
SRC = main.c
OBJ = ${SRC:.c=.o}
LIB = -L ./MLX42/build -L ./LIBFT -lmlx42 -lft -ldl -lglfw -pthread -lm
INC = -I minirt.h -I ./MLX42/include -I ./LIBFT
FLAG = -Wextra -Wall -Werror

all: ${NAME}

${NAME}: ${MLX42} ${LIBFT} ${OBJ} 
	@cc ${FLAG} -o ${NAME} ${OBJ} ${INC} ${LIB}

${MLX42}:
	@make -C ./MLX42/build

${LIBFT}:
	@make -C ./LIBFT

${OBJ}: ${SRC}
	@cc ${FLAG} -c ${SRC} ${INC}

clean:
	@rm -rf ${OBJ}
	@make clean -C ./LIBFT

fclean: clean
	@rm -rf ${NAME}
	@rm -rf ${MLX42}
	@rm -rf ${LIBFT}

re: fclean all

.PHONY: all, clean, fclean, re
