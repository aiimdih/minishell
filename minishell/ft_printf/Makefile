
CC = cc
CFLAGS = -Wall -Wextra -Werror

NAME = libftprintf.a

SRCS =  utils.c  handle_print.c ft_printf.c ft_memset_and_ptr.c

BONUS = ft_printf_bonus.c utils_bonus.c  handle_print_bonus.c ft_memset_and_ptr_bonus.c

OBJS = $(SRCS:.c=.o)

BONUS_OBJS = $(BONUS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

clean:
	rm -f $(OBJS) $(BONUS_OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

bonus : $(BONUS_OBJS)
	ar rcs $(NAME) $(BONUS_OBJS)

.PHONY: all clean fclean re bonus
