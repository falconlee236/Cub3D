NAME=cub3D
CFLAGS=cc -Wall -Wextra -Werror -g

SRCS=cub3d.c \
		$(wildcard parse/*.c) \
		$(wildcard raycast/*.c) \
		$(wildcard player/*.c) \
		$(wildcard vector/*.c)

all: $(NAME)

$(NAME):
	@$(MAKE) -C mlx all
	@$(MAKE) -C libft all
	$(CFLAGS) -o $(NAME) $(SRCS) -L ./mlx -lmlx -framework OpenGL -framework Appkit -L ./libft -lft

clean:
	@$(MAKE) -C mlx clean
	@$(MAKE) -C libft clean

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C mlx clean
	@$(MAKE) -C libft fclean

re: fclean all

.PHONY: all clean fclean re
