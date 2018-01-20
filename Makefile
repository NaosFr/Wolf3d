# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ncella <ncella@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/22 14:43:15 by ncella            #+#    #+#              #
#    Updated: 2017/12/27 18:29:23 by ncella           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d

SRC_NAME = main.c ft_key.c ray_casting.c ft_read.c  ft_check_map.c ft_convert_to_int.c ft_init.c ft_draw.c 
SRC = $(addprefix srcs/, $(SRC_NAME))
OBJ = $(patsubst srcs/%.c, obj/%.o, $(SRC))
CFLAGS = -g -Ofast -flto -march=native -Wall -Wextra -Werror -g -I libft/ -I minilibx/
LIBS = -framework OpenGL -framework AppKit libft/libft.a minilibx/libmlx.a 

all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft/ fclean && make -C libft/
	@gcc -g $(CFLAGS) -o $(NAME) $(LIBS) $(OBJ)
	@echo "\033[32mWolf3d compiled [ ✔ ]"

obj/%.o: srcs/%.c
	@mkdir -p obj
	@gcc $(CFLAGS) -c $< -o $@

clean:
	@rm -rf obj/
	@make -C libft/ fclean
	@echo "\033[32mWolf3d cleaned [ ✔ ]"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[32mWolf3d fcleaned [ ✔ ]"

re: fclean all

.PHONY: all clean fclean re
