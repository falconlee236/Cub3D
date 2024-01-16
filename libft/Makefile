# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sangylee <sangylee@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/16 22:07:12 by sangylee          #+#    #+#              #
#    Updated: 2023/07/14 15:03:14 by sangylee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=cc
FLAG=-Wall -Wextra -Werror
SRCS=ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
	ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
	ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
	ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
	ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c \
	ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
	ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
	ft_atoll.c\
	get_next_line.c get_next_line_utils.c\
	format_c.c format_d.c format_p.c\
	format_s.c format_u.c format_x.c\
	format_x_upper.c ft_printf.c

SRCS_BONUS =ft_lstnew_bonus.c \
			ft_lstadd_front_bonus.c \
			ft_lstsize_bonus.c \
			ft_lstlast_bonus.c \
			ft_lstadd_back_bonus.c \
			ft_lstdelone_bonus.c \
			ft_lstclear_bonus.c \
			ft_lstiter_bonus.c \
			ft_lstmap_bonus.c \
			get_next_line_bonus.c\
			get_next_line_utils_bonus.c
			
OBJS=$(SRCS:.c=.o)
OBJS_BONUS=$(SRCS_BONUS:.c=.o)
NAME=libft.a

ifdef WITH_BONUS
    OBJS_FILES = $(OBJS) $(OBJS_BONUS)
else
    OBJS_FILES = $(OBJS)
endif

all: $(NAME)

%.o:%.c
	$(CC) $(FLAG) -c $< -o $@

$(NAME): $(OBJS_FILES)
	ar -rcs $@ $^

bonus:
	make WITH_BONUS=1 all

clean:
	rm -rf $(OBJS) $(OBJS_BONUS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: bonus all clean fclean re