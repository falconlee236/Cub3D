NAME=cub3D
CFLAGS=cc -Wall -Wextra -Werror -o

SRCS=cub3d.c key_hook_event.c init_struct.c \
		main_loop.c raycast_util.c\
		$(wildcard vector/*.c)

all: $(NAME)

$(NAME):
	@$(MAKE) -C mlx all
	@$(MAKE) -C libft all
	$(CFLAGS) $(NAME) $(SRCS) -L ./mlx -lmlx -framework OpenGL -framework Appkit -L ./libft -lft

clean:
	@$(MAKE) -C mlx clean
	@$(MAKE) -C libft clean

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C mlx clean
	@$(MAKE) -C libft fclean

re: fclean all

.PHONY: all clean fclean re