NAME=cub3D
CC=cc
CFLAGS=-Wall -Wextra -Werror

SRCS_MAND=mandatory/cub3d.c \
		mandatory/utils.c \
		$(wildcard mandatory/parse/*.c) \
		$(wildcard mandatory/raycast/*.c) \
		$(wildcard mandatory/player/*.c) \
		$(wildcard mandatory/vector/*.c)
OBJS_MAND=mandatory/cub3d.o \
		mandatory/utils.o \
		$(wildcard mandatory/parse/*.o) \
		$(wildcard mandatory/raycast/*.o) \
		$(wildcard mandatory/player/*.o) \
		$(wildcard mandatory/vector/*.o)

NAME_BONUS=cub3D_bonus
SRCS_BONUS=bonus/cub3d_bonus.c \
		bonus/utils_bonus.c \
		$(wildcard bonus/parse/*.c) \
		$(wildcard bonus/raycast/*.c) \
		$(wildcard bonus/player/*.c) \
		$(wildcard bonus/vector/*.c)
OBJS_BONUS=bonus/cub3d_bonus.o \
		bonus/utils_bonus.o \
		$(wildcard bonus/parse/*.o) \
		$(wildcard bonus/raycast/*.o) \
		$(wildcard bonus/player/*.o) \
		$(wildcard bonus/vector/*.o)

all: $(NAME)

$(NAME): $(SRCS_MAND)
	@$(MAKE) -C mlx all
	@$(MAKE) -C libft all
	$(CC) $(CFLAGS) -o $(NAME) $(SRCS_MAND) -L ./mlx -lmlx -framework OpenGL -framework Appkit -L ./libft -lft

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(SRCS_BONUS)
	@$(MAKE) -C mlx all
	@$(MAKE) -C libft all
	$(CC) $(CFLAGS) -o $(NAME_BONUS) $(SRCS_BONUS) -L ./mlx -lmlx -framework OpenGL -framework Appkit -L ./libft -lft

clean:
	rm -rf $(OBJS_MAND) $(OBJS_BONUS)
	@$(MAKE) -C mlx clean
	@$(MAKE) -C libft clean

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)
	@$(MAKE) -C mlx clean
	@$(MAKE) -C libft fclean

re: fclean all

.PHONY: all clean fclean re bonus
